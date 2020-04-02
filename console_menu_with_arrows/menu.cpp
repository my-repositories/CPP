#include "menu.hpp"

Menu::Menu(const std::vector<std::string>& items, const std::string& title, const std::string cursor)
{
    this->items = items;
    this->title = title;
    this->cursor = cursor;
    this->cursorSize = cursor.size();
    this->itemsCount = items.size();

    this->position.x.title = 7;
    this->position.x.items = 20;
    this->position.x.cursor = this->position.x.items - this->cursorSize;

    this->position.y.first = 7;
    this->position.y.last = this->position.y.first + 9;

    this->elementsPerPage = 7;
    this->maxPage = (this->itemsCount - 1) / this->elementsPerPage;
    this->page = 0;

    this->console = GetStdHandle(STD_OUTPUT_HANDLE);
    this->coords = { 0, 0 };
}

int Menu::getSelectedIndex()
{
    size_t currentPositionY = this->position.y.first;

    this->printTitle();
    this->gotoXY(this->position.x.cursor, currentPositionY);
    std::cout << cursor;

    while (true)
    {
        this->printSubTitle();
        this->printItems();
        this->printNavigation();

        system("pause>nul");

        if (GetAsyncKeyState(VK_RETURN))
        {
            const int menuItem = currentPositionY - this->position.y.first;

            if (menuItem < 7)
            {
                const size_t selectedIndex = currentPositionY - this->position.y.first + this->page * this->elementsPerPage;
                if (selectedIndex < this->itemsCount)
                {
                    return selectedIndex;
                }
            }
            else if (menuItem == 9)
            {
                return -1;
            }
            else if (7 == menuItem && this->page > 0)
            {
                --this->page;
            }
            else if (8 == menuItem && this->page < this->maxPage)
            {
                ++this->page;
            }

            continue;
        }

        this->handleArrowKeys(currentPositionY);
    }
}

void Menu::printTitle()
{
    this->gotoXY(this->position.x.title, this->position.y.first - 3);
    std::cout << this->title;
}

void Menu::printSubTitle()
{
    std::stringstream ss;
    ss << "Page: " << 1 + this->page << '/' << 1 + this->maxPage;
    this->printLine(ss.str(), this->position.x.title, this->position.y.first - 2);
}

void Menu::printItems()
{
    if (!this->itemsCount)
    {
        return;
    }

    const size_t maxItemIndex = this->getCountPrintableItems();

    for (size_t index = 0; index < maxItemIndex; ++index)
    {
        std::stringstream ss;
        ss << (1 + index) << +") " << this->items[index + this->elementsPerPage * this->page];

        this->printLine(ss.str(), this->position.x.items, index + this->position.y.first);
    }

    for (size_t i = this->elementsPerPage - 1; i >= maxItemIndex; --i)
    {
        this->printLine("--", this->position.x.items, i + this->position.y.first);
    }
}

void Menu::printNavigation()
{
    if (this->page == 0)
    {
        this->printLine("-- Prev Page (DISABLED)", this->position.x.items, this->elementsPerPage + this->position.y.first);
    }
    else
    {
        this->printLine("8) Prev Page", this->position.x.items, this->elementsPerPage + this->position.y.first);
    }

    if (this->page == this->maxPage)
    {
        this->printLine("-- Next Page (DISABLED)", this->position.x.items, this->elementsPerPage + this->position.y.first + 1);
    }
    else
    {
        this->printLine("9) Next Page", this->position.x.items, this->elementsPerPage + this->position.y.first + 1);
    }

    this->printLine("0) Quit Program", this->position.x.items, this->elementsPerPage + this->position.y.first + 2);
    std::cout << std::endl << std::endl;
}

void Menu::handleArrowKeys(size_t& currentPositionY)
{
    if (GetAsyncKeyState(VK_LEFT) && this->page > 0)
    {
        --this->page;
        return;
    }

    if (GetAsyncKeyState(VK_RIGHT) && this->page < this->maxPage)
    {
        ++this->page;
        return;
    }

    const bool isKeyUpPressed = GetAsyncKeyState(VK_UP) && currentPositionY > this->position.y.first;
    const bool isKeyDownPressed = GetAsyncKeyState(VK_DOWN) && currentPositionY < this->position.y.last;

    if (isKeyUpPressed || isKeyDownPressed)
    {
        this->gotoXY(this->position.x.cursor, currentPositionY);
        this->printCharSeveralTimes(' ', this->cursorSize);

        currentPositionY += isKeyUpPressed ? -1 : 1;

        this->gotoXY(this->position.x.cursor, currentPositionY);
        std::cout << cursor;
    }
}

void Menu::printLine(const std::string& text, const size_t x, const size_t y)
{
    this->gotoXY(x, y);

    const size_t textSize = text.size();
    constexpr const size_t maxTextSize = 56;

    if (textSize > maxTextSize)
    {
        std::cout << text.substr(0, 53) << "...";
    }
    else
    {
        std::cout << text;
        this->printCharSeveralTimes(' ', maxTextSize - textSize);
    }
}

void Menu::printCharSeveralTimes(const char ch, const size_t times)
{
    const std::string filler(times, ch);
    std::cout << filler;
}

void Menu::gotoXY(const size_t x, const size_t y)
{
    this->coords.X = static_cast<short>(x);
    this->coords.Y = static_cast<short>(y);
    SetConsoleCursorPosition(this->console, this->coords);
}

int Menu::getCountPrintableItems()
{
    if (this->page == 0)
    {
        if (this->itemsCount < this->elementsPerPage)
        {
            return this->itemsCount;
        }

        return this->elementsPerPage;
    }

    if (this->itemsCount < this->elementsPerPage)
    {
        return 0;
    }

    const size_t result = this->itemsCount - this->elementsPerPage * this->page;

    if (result < 0)
    {
        return 0;
    }

    return result < this->elementsPerPage
        ? result
        : this->elementsPerPage;
}
