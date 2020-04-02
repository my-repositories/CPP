#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <windows.h>

class Menu
{
public:

    explicit Menu(const std::vector<std::string>& items, const std::string& title, const std::string cursor = "->");

    int getSelectedIndex();

private:
    std::vector<std::string> items;
    std::string cursor, title;
    HANDLE console;
    COORD coords;
    size_t page, maxPage, elementsPerPage, itemsCount, cursorSize;
    struct {
        struct {
            size_t title, cursor, items;
        } x;

        struct {
            size_t first, last;
        } y;
    } position;

    void printTitle();

    void printSubTitle();

    void printItems();

    void printNavigation();

    void handleArrowKeys(size_t& currentPositionY);

    void printLine(const std::string& text, const size_t x, const size_t y);

    void printCharSeveralTimes(const char ch, const size_t times);

    void gotoXY(const size_t x, const size_t y);

    int getCountPrintableItems();
};

#endif // MENU_HPP