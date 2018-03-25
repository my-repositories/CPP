#include "WinApp.h"

HWND Application::edit1 = NULL;
HWND Application::edit2 = NULL;

HWND Application::label1 = NULL;
HWND Application::label2 = NULL;

int Application::button_yes = 101;
int Application::button_no = 102;

int Application::combobox_color = 107;
int Application::combobox_num = 108;

Application::Application(char *appName, const int width, const int height)
{
    WNDCLASSEX wcex;
    hWnd = NULL;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = &Application::WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(NULL);
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = appName;
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wcex))
        return;

    hWnd = CreateWindowEx(
        0,
        appName,
        appName,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        width,
        height,
        HWND_DESKTOP,
        NULL,
        0,
        NULL
    );
}

Application::~Application()
{
    SendMessage(hWnd, WM_CLOSE, NULL, NULL);
}

void Application::Run()
{
    if (!hWnd)
        return;

    ShowWindow(hWnd, SW_SHOWDEFAULT);
    UpdateWindow(hWnd);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        if (msg.message == WM_QUIT) break;
        DispatchMessage(&msg);
    }
}

LRESULT WINAPI Application::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        /* Create label */
        label1 = CreateWindow("STATIC",
            "Label1",
            WS_CHILD | WS_VISIBLE,
            300,      // x position
            25,       // y position
            150,      // width
            20,       // height
            hWnd,
            (HMENU)0,
            GetModuleHandle(NULL),
            NULL
        );

        /* Create label */
        label2 = CreateWindow("STATIC",
            "Label2",
            WS_CHILD | WS_VISIBLE,
            300,      // x position
            75,       // y position
            150,      // width
            20,       // height
            hWnd,
            (HMENU)0,
            GetModuleHandle(NULL),
            NULL
        );

        /* Create editbox */
        edit1 = CreateWindowEx(NULL,
            "EDIT",
            "Edit box 1",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
            100,        // x position
            225,        // y position
            150,        // width
            20,         // height
            hWnd,
            (HMENU)0,
            GetModuleHandle(NULL),
            NULL
        );

        /* Create editbox */
        edit2 = CreateWindowEx(NULL,
            "EDIT",
            "Edit box 2",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
            100,        // x position
            275,        // y position
            150,        // width
            20,         // height
            hWnd,
            (HMENU)0,
            GetModuleHandle(NULL),
            NULL
        );

        /* Create button */
        HWND hWndYes = CreateWindowEx(
            NULL,
            "BUTTON",
            "Yes",       // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            300,        // x position 
            225,        // y position 
            50,         // Button width
            25,         // Button height
            hWnd,       // Parent window
            (HMENU)button_yes,
            GetModuleHandle(NULL),
            NULL
        );

        /* Create button */
        HWND hWndNo = CreateWindowEx(
            NULL,
            "BUTTON",
            "No",       // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            300,        // x position 
            275,        // y position 
            50,         // Button width
            25,         // Button height
            hWnd,       // Parent window
            (HMENU)button_no,
            GetModuleHandle(NULL),
            NULL
        );

        /* Create color combobox */
        HWND hWndColor = CreateWindowEx(
            NULL,
            "COMBOBOX",
            "Color",
            CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
            100,      // x position
            25,       // y position
            150,      // width
            200,      // height
            hWnd,
            (HMENU)combobox_color,
            GetModuleHandle(NULL), //(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL
        );

        /* Select default item */
        PostMessage(hWndColor, CB_SETCURSEL, 2, 0);

        /* Add items to combobox */
        const int COLOR_ITEMS_COUNT = 5;
        const char colors[COLOR_ITEMS_COUNT][8] = { "Red", "Green", "Blue", "Black", "White" };
        
        for (int i = 0; i < COLOR_ITEMS_COUNT; i++)
        {
            SendMessage(hWndColor, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)colors[i]);
        }

        /* Create num combobox */
        HWND hWndNum = CreateWindowEx(
            NULL,
            "COMBOBOX",
            "Num",
            CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
            100,    // x position
            75,     // y position
            150,    // width
            200,    // height
            hWnd,
            (HMENU)combobox_num,
            GetModuleHandle(NULL), //(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL
        );

        /* Select default item */
        PostMessage(hWndNum, CB_SETCURSEL, 1, 0);

        /* Add items to combobox */
        const int NUM_ITEMS_COUNT = 3;
        const char nums[NUM_ITEMS_COUNT][8] = { "Five", "Six", "Seven" };

        for (int i = 0; i < NUM_ITEMS_COUNT; i++)
        {
            SendMessage(hWndNum, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)nums[i]);
        }
        break;
    }
    case WM_COMMAND:
    {
        /* Button pressed */
        if (HIWORD(wParam) == BN_CLICKED)
        {
            Application::HandleButton(hWnd, LOWORD(wParam));
        }
        /* Combobox item change*/
        else if (HIWORD(wParam) == CBN_SELCHANGE)
        {
            int ItemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
            char ListItem[32];
            SendMessage((HWND)lParam, (UINT)CB_GETLBTEXT, (WPARAM)ItemIndex, (LPARAM)ListItem);

            Application::HandleCombobox(hWnd, LOWORD(wParam), ItemIndex, ListItem);
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

void Application::HandleCombobox(HWND hWnd, int item, int index, char *value)
{
    if (item == combobox_color)
    {
        MessageBox(hWnd, value, "Color Selected", MB_OK);
    }
    else if (item == combobox_num)
    {
        MessageBox(hWnd, value, "Num Selected", MB_OK);
    }
}

void Application::HandleButton(HWND hWnd, int item)
{
    if (item == button_yes)
    {
        MessageBox(hWnd, "Yes", "Button Pressed", MB_OK);

        char text[32];
        SendMessage(edit1, WM_GETTEXT, (WPARAM)32, (LPARAM)text);

        SetWindowText(label1, text);
        SetWindowText(label2, text);
    }
    else if (item == button_no)
    {
        MessageBox(hWnd, "No", "Button Pressed", MB_OK);
        
        char text[32];
        SendMessage(edit2, WM_GETTEXT, (WPARAM)32, (LPARAM)text);

        SetWindowText(label1, text);
        SetWindowText(label2, text);
    }
}
