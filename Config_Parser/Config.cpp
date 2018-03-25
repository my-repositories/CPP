#include "Config.h"

Config::Config(std::string fileName)
{
    ParseXml(fileName);
    ParseIni("settings.ini");
}

Config::~Config() {}

void Config::ParseIni(std::string fileName)
{
    char szPath[MAX_PATH];
    GetCurrentDirectory(sizeof(szPath), szPath);
    lstrcat(szPath, "\\");
    lstrcat(szPath, fileName.c_str());

    if (!FileExists(szPath))
    {
        return;
    }

    ini.open(fileName);
    while (getline(ini, buff))
    {
        if (buff.find("KEY_GODMODE") != std::string::npos)
        {
            ReadKey(hotkey.godMode);
        }
        if (buff.find("KEY_NORELOAD") != std::string::npos)
        {
            ReadKey(hotkey.noReload);
        }
        if (buff.find("KEY_MONEY") != std::string::npos)
        {
            ReadKey(hotkey.money);
        }
        if (buff.find("KEY_EXPERIENCE") != std::string::npos)
        {
            ReadKey(hotkey.experience);
        }
        if (buff.find("AMOUNT_MONEY") != std::string::npos)
        {
            ReadAmount(amountMoney, money.type);
        }
        if (buff.find("AMOUNT_EXPERIENCE") != std::string::npos)
        {
            ReadAmount(amountExperience, experience.type);
        }
    }
    ini.close();
}

void Config::ReadAmount(amount& data, std::string& type)
{
    offset = buff.find("=") + 1;
    buff = buff.substr(offset);
    buff = buff.substr(buff.find_first_not_of(' '));

    if (type == "Float")
    {
        data.value.f = stof(buff);
    }
    else
    {
        data.value.i = stoi(buff);
    }
    data.type = type;
}

void Config::ReadKey(hot::keys& hotkey)
{
    offset = buff.find("=") + 1;
    buff = buff.substr(offset);
    hotkey.name = buff.substr(buff.find_first_not_of(' '));
    hotkey.code = key2code(hotkey.name);
}

int Config::Key2code(std::string key)
{
    size_t len = key.length();
    switch (len)
    {
    case 1: return VkKeyScan(key[0]) & 0xff;
    case 2:
    case 3: return VK_F1 - 1 + atoi(key.substr(1).c_str());
    case 4:
    case 5: return VK_NUMPAD0 + atoi(key.substr(3).c_str());
    case 7:
    case 8: return VK_NUMPAD0 + atoi(key.substr(6).c_str());
    }
    return -1;
}

void Config::ParseXml(std::string& file)
{
    xml.open(file);
    while (getline(xml, buff))
    {
        if (buff.find("<Description>\"HEALTH\"</Description>") != std::string::npos)
        {
            ReadEntry(health);
        }
        if (buff.find("<Description>\"ARMOUR\"</Description>") != std::string::npos)
        {
            ReadEntry(armour);
        }
        if (buff.find("<Description>\"MONEY\"</Description>") != std::string::npos)
        {
            ReadEntry(money);
        }
        if (buff.find("<Description>\"EXPERIENCE\"</Description>") != std::string::npos)
        {
            ReadEntry(experience);
        }
        if (buff.find("<Description>\"MAGAZINE\"</Description>") != std::string::npos)
        {
            ReadEntry(magazine);
        }
        if (buff.find("<Description>\"AMMO\"</Description>") != std::string::npos)
        {
            ReadEntry(ammo);
        }
        if (buff.find("<Description>\"GREN\"</Description>") != std::string::npos)
        {
            ReadEntry(gren);
        }
        if (buff.find("<Description>\"MAXHEALTH\"</Description>") != std::string::npos)
        {
            ReadValue(maxHealth);
        }
        if (buff.find("<Description>\"PROCESSNAME\"</Description>") != std::string::npos)
        {
            processName = ReadSettings();
        }
    }
    xml.close();
}

void Config::ReadEntry(entrys& data)
{
    while (getline(xml, buff))
    {
        if (buff.find("<VariableType>") != std::string::npos)
        {
            ReadType(data);
        }
        if (buff.find("<Address>") != std::string::npos)
        {
            ReadAddress(data);
        }
        if (buff.find("<Offsets>") != std::string::npos)
        {
            ReadOffsets(data);
            break;
        }
    }
}

void Config::ReadType(entrys& data)
{
    offset = buff.find(">") + 1;
    size = buff.find("/") - offset - 1;
    data.type = buff.substr(offset, size);

    if (data.type == "Byte")
    {
        data.size = 1;
    }
    else if (data.type == "2 Bytes")
    {
        data.size = 2;
    }
    else
    {
        data.size = 4;
    }
}

void Config::ReadAddress(entrys& data)
{
    // read Module
    offset = buff.find(">") + 2;
    size = buff.find("+") - offset - 1;
    data.module = buff.substr(offset, size);

    // read Base Address
    offset = buff.find("+") + 1;
    size = buff.find("/") - offset - 1;
    data.address = std::stoul(buff.substr(offset, size), nullptr, 16);
}

void Config::ReadOffsets(entrys& data)
{
    while (getline(xml, buff))
    {
        if (buff.find("</Offsets>") != std::string::npos)
        {
            break;
        }

        offset = buff.find(">") + 1;
        size = buff.find("/") - offset - 1;
        data.offsets[data.count] = std::stoul(buff.substr(offset, size), nullptr, 16);
        ++data.count;
    }
    --data.count;
}

void Config::ReadValue(amount& amount)
{
    while (getline(xml, buff))
    {
        if (buff.find("<VariableType>") != std::string::npos)
        {
            offset = buff.find(">") + 1;
            size = buff.find("/") - offset - 1;
            amount.type = buff.substr(offset, size);

            if ("Float" == amount.type)
            {
                amount.value.f = stof(readSettings());
            }
            else
            {
                amount.value.i = stoi(readSettings());
            }
            return;
        }
    }
}

std::string Config::ReadSettings()
{
    while (getline(xml, buff))
    {
        if (buff.find("<Address>") != std::string::npos)
        {
            offset = buff.find(">") + 1;
            size = buff.find("/") - offset - 1;
            return buff.substr(offset, size);
        }
    }
    return NULL;
}

BOOL Config::FileExists(LPCTSTR szPath)
{
    DWORD dwAttrib = GetFileAttributes(szPath);

    return (dwAttrib != INVALID_FILE_ATTRIBUTES
        && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}
