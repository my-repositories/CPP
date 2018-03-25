#include "WinApp.h"

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{

    Application app("WinApi Application", 640, 480);
    app.Run();

    return 0;
}
