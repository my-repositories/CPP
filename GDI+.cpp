#include<windows.h>

void DrawText()
{
    TCHAR* str = TEXT("Hello DrawText !!!");
    HWND wnd = GetForegroundWindow();
    HDC dc = GetDC(wnd);
    RECT rc;
    HFONT font;
    HGDIOBJ old;

    font = CreateFont(-24, 0, 0, 0, 0, ANSI_CHARSET, 0U, 0U, 0U, 0U, 0U, 0U, 0U, TEXT("Arial"));
    old = SelectObject(dc, font);

    GetClientRect(wnd, &rc);
    rc.top = 150;
    
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, 0x0000FF00);  // цвет текста(зелённый)

                                   // вывести текст по середине(горизонтали)
    DrawText(dc, str, lstrlen(str), &rc, DT_CENTER);

    SelectObject(dc, old);
    ReleaseDC(wnd, dc);
    DeleteObject(font);
    getchar();
}

void GetRGB()
{
    static POINT pos;
    static HDC hdcScreen;
    static COLORREF pixel;

    GetCursorPos(&pos);
    hdcScreen = ::GetDC(NULL);
    pixel = ::GetPixel(hdcScreen, pos.x+2, pos.y+2);
    ReleaseDC(NULL, hdcScreen);

    if (pixel != CLR_INVALID)
    {
        r = GetRValue(pixel);
        g = GetGValue(pixel);
        b = GetBValue(pixel);
    }
}

void DrawOnDesktop()
{
    /* hide console window */
    ShowWindow(FindWindowA("ConsoleWindowClass", NULL), SW_MINIMIZE);

    /* Calling GetDC with argument 0 retrieves the desktop's DC */
    HDC hDC_Desktop = GetDC(0);

    /* Draw a simple blue rectangle on the desktop */
    RECT rect = { 20, 20, 200, 200 };
    HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));

    for(;!GetAsyncKeyState(27); Sleep(10))
        FillRect(hDC_Desktop, &rect, blueBrush);
}

int main()
{
    // Получаем DC для рисования
    HWND hWnd = GetConsoleWindow();

    HDC hDC = GetDC(hWnd);

    // Получаем размер клиентской области окна
    RECT rc;
    GetClientRect(hWnd, &rc);

    // Создаем Pen
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

    // Выбираем свой Pen в DC, запоминаем старый Pen
    HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

    // Перемещаем точку рисования в левый верхний угол окна
    MoveToEx(hDC, rc.left, rc.top, NULL);
    // Рисуем линию в правый нижний угол
    LineTo(hDC, rc.right, rc.bottom);

    // Выбираем старый Pen в DC (освобождаем свой Pen из DC)
    SelectObject(hDC, hOldPen);

    // Удаляем Pen
    DeleteObject(hPen);

    // Освобождаем DC
    ReleaseDC(hWnd, hDC);
}

/*
        SelectObject(hdc, GetStockObject(DC_PEN));
        SetDCPenColor(hdc, RGB(150, 50, 30));
*/
