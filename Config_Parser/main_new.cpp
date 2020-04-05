#include <fstream>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <vector>
#include <Windows.h>

struct Entry
{
    short size{};
    short offsetsCount{};
    DWORD offsets[5]{};
    DWORD_PTR address{};
    char module[32];
    char variableType[32];
    char description[56];
};

namespace Readers
{
    class TableSetter
    {
    public:
        explicit TableSetter(std::ifstream* file)
        {
            this->file = file;
        }

        virtual ~TableSetter() {}

        virtual void set(const std::string& buffer, Entry& entry) = 0;

    protected:
        std::ifstream* file;
    };

    class DescriptionSetter : public TableSetter
    {
    public:
        explicit DescriptionSetter(std::ifstream* file)
            : TableSetter(file)
        {}

        virtual ~DescriptionSetter() {}

        void set(const std::string& buffer, Entry& entry) override
        {
            if (buffer.find("<Description>") == std::string::npos)
            {
                return;
            }

            size_t offset = buffer.find('>') + 2;
            size_t length = buffer.find('/') - offset - 2;
            strcpy_s(entry.description, (char*) (buffer.substr(offset, length).c_str()));
        }
    };

    class VariableTypeSetter : public TableSetter
    {
    public:
        explicit VariableTypeSetter(std::ifstream* file)
                : TableSetter(file)
        {}

        virtual ~VariableTypeSetter() {}

        void set(const std::string& buffer, Entry& entry) override
        {
            if (buffer.find("<VariableType>") == std::string::npos)
            {
                return;
            }

            size_t offset = buffer.find('>') + 1;
            size_t length = buffer.find('/') - offset - 1;

            strcpy_s(entry.variableType, (char*) (buffer.substr(offset, length).c_str()));

            if (!strcmp(entry.variableType, "Byte"))
            {
                entry.size = 1;
            }
            else if (!strcmp(entry.variableType, "2 Bytes"))
            {
                entry.size = 2;
            }
            else
            {
                entry.size = 4;
            }

        }
    };

    class AddressSetter : public TableSetter
    {
    public:
        explicit AddressSetter(std::ifstream* file)
                : TableSetter(file)
        {}

        virtual ~AddressSetter() {}

        void set(const std::string& buffer, Entry& entry) override
        {
            if (buffer.find("<Address>") == std::string::npos || !strcmp(entry.variableType, (char*)"Auto Assembler Script"))
            {
                return;
            }

            // set Module
            size_t offset = buffer.find('>') + 2;
            size_t length = buffer.find('+') - offset - 1;
            strcpy_s(entry.module, (char*) (buffer.substr(offset, length).c_str()));

            // set Address
            offset = buffer.find('+') + 1;
            length = buffer.find('/') - offset - 1;
            entry.address = std::stoul(buffer.substr(offset, length), nullptr, 16);
        }
    };

    class OffsetsSetter : public TableSetter
    {
    public:
        explicit OffsetsSetter(std::ifstream* file)
                : TableSetter(file)
        {}

        virtual ~OffsetsSetter() {}

        void set(const std::string& buffer, Entry& entry) override
        {
            if (buffer.find("<Offsets>") == std::string::npos)
            {
                return;
            }

            std::string localBuffer;

            while (getline(*this->file, localBuffer))
            {
                if (localBuffer.find("</Offsets>") != std::string::npos)
                {
                    break;
                }

                size_t offset = localBuffer.find('>') + 1;
                size_t length = localBuffer.find('/') - offset - 1;

                auto value = localBuffer.substr(offset, length);
                entry.offsets[entry.offsetsCount] = std::stoul(value, nullptr, 16);
                ++entry.offsetsCount;
            }
        }
    };

    class TableMediator
    {
    public:
        explicit TableMediator(std::ifstream* file)
        {
            this->setters.push_back(new DescriptionSetter(file));
            this->setters.push_back(new VariableTypeSetter(file));
            this->setters.push_back(new AddressSetter(file));
            this->setters.push_back(new OffsetsSetter(file));
        }

        ~TableMediator()
        {
            for (TableSetter* setter : this->setters)
            {
                delete setter;
            }

            this->setters.clear();
        }

        void setProps(const std::string& buffer, Entry& entry)
        {
            for (TableSetter* setter : this->setters)
            {
                setter->set(buffer, entry);
            }
        }

    private:
        std::vector<TableSetter*> setters;
    };

    class TableReader
    {
    public:
        explicit TableReader(const char* fileName)
        {
            this->fileName = (char*)fileName;
            this->file.open(this->fileName);
            this->tableMediator = new TableMediator(&this->file);
        }

        ~TableReader()
        {
            delete this->tableMediator;
            this->file.close();
        }

        std::vector<Entry> read()
        {
            std::vector<Entry> entries;
            char szPath[MAX_PATH];

            GetCurrentDirectory(sizeof(szPath), szPath);
            lstrcat(szPath, "\\");
            lstrcat(szPath, this->fileName);

            if (!std::filesystem::exists(szPath))
            {
                return entries;
            }

            return this->readEntries();
        }

    private:
        char* fileName;
        std::ifstream file;
        TableMediator* tableMediator;

        std::vector<Entry> readEntries()
        {
            std::string buffer;
            std::vector<Entry> entries;

            while (getline(this->file, buffer))
            {
                if (buffer.find("<CheatEntries>") != std::string::npos)
                {
                    while (getline(this->file, buffer))
                    {
                        if (buffer.find("</CheatEntries>") != std::string::npos)
                        {
                            break;
                        }

                        entries.push_back(this->readEntry());
                    }
                }
            }

            return entries;
        }

        Entry readEntry()
        {
            std::string buffer;
            Entry entry{};

            while (getline(this->file, buffer))
            {
                if (buffer.find("</CheatEntry>") != std::string::npos)
                {
                    break;
                }

                this->tableMediator->setProps(buffer, entry);
            }

            return entry;
        }

    };
}

int main()
{
    Readers::TableReader reader("kf.CT");
    auto data = reader.read();

    std::cout << "size: " << data.size() << std::endl;

    return 0;
}

