bool AppIsRun()
{
    HANDLE mutex = CreateMutex(NULL, TRUE, "MyApplication");

    if (mutex == NULL || GetLastError() == ERROR_ALREADY_EXISTS)
    {
        HWND existingApp = FindWindow(0, TEXT("MyApplication"));
        if (existingApp)
        {
            ShowWindow(existingApp, SW_RESTORE);
            SetForegroundWindow(existingApp);
            return true;
        }
    }

    return false;
}
