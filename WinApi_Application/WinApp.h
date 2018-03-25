#pragma once
#ifndef WINAPP_H
#define WINAPP_H

#include <windows.h> 

class Application
{
public:
    explicit Application(char *appName, const int width, const int height);
    ~Application();
    void Run();

private:
    HWND  hWnd;
    static HWND edit1, edit2;
    static HWND label1, label2;
    static int button_yes, button_no;
    static int combobox_color, combobox_num;

    static LRESULT WINAPI WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static void HandleCombobox(HWND hWnd, int item, int index, char *value);
    static void HandleButton(HWND hWnd, int item);
};

#endif // !WINAPP_H
