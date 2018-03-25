
// @_@
if (release)
{
    SendMessage(hwnd, WM_KEYDOWN, key, NULL);
    Sleep(100);
    SendMessage(hwnd, WM_KEYUP, key, NULL);
}
else
{
    PostMessage(hwnd, WM_KEYDOWN, key, MapVirtualKey(key, MAPVK_VK_TO_VSC));
    Sleep(100);
    PostMessage(hwnd, WM_KEYUP, key, MapVirtualKey(key, MAPVK_VK_TO_VSC));
}

// SHIFT + A
keybd_event(VK_LSHIFT, 0, 0, 0);
keybd_event(VkKeyScan('a'), 0, 0, 0);
keybd_event(VkKeyScan('a'), 0, KEYEVENTF_KEYUP, 0);
keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0);

// mouse
SetMousePosition(600, 235);
GetCursorPos(&mouse);

// Mouse CLick
    INPUT Input = { 0 };
    // left down 
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = (button == 2 ? MOUSEEVENTF_RIGHTDOWN : MOUSEEVENTF_LEFTDOWN);
    ::SendInput(1, &Input, sizeof(INPUT));

    // left up
    ::ZeroMemory(&Input, sizeof(INPUT));
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = (button == 2 ? MOUSEEVENTF_RIGHTUP : MOUSEEVENTF_LEFTUP);
    ::SendInput(1, &Input, sizeof(INPUT));
    
// set mouse position
void setMousePosition(long x, long y)
{
    long fScreenWidth = GetSystemMetrics(SM_CXSCREEN) - 1;
    long fScreenHeight = GetSystemMetrics(SM_CYSCREEN) - 1;

    // http://msdn.microsoft.com/en-us/library/ms646260(VS.85).aspx
    // If MOUSEEVENTF_ABSOLUTE value is specified, dx and dy contain normalized absolute coordinates between 0 and 65,535.
    // The event procedure maps these coordinates onto the display surface.
    // Coordinate (0,0) maps onto the upper-left corner of the display surface, (65535,65535) maps onto the lower-right corner.
    float fx = x * (65535.0f / fScreenWidth);
    float fy = y * (65535.0f / fScreenHeight);

    INPUT Input = { 0 };
    Input.type = INPUT_MOUSE;

    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

    Input.mi.dx = (long)fx;
    Input.mi.dy = (long)fy;

    SendInput(1, &Input, sizeof(INPUT));
}

// get pixel color

    HDC hDC_Desktop = GetDC(0);
    COLORREF color;
    POINT mouse;

    GetCursorPos(&mouse);
    color = GetPixel(hDC_Desktop, mouse.x, mouse.y);
    printf("RGB(%i, %i, %i)\n", GetRValue(color), GetGValue(color), GetBValue(color));
