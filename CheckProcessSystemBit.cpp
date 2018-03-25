#include<Windows.h>
#include<Iostream>

BOOL IsWow64(HANDLE hProc)
{
    BOOL bIsWow64 = FALSE;

    typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

    LPFN_ISWOW64PROCESS fnIsWow64Process;
    fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
        GetModuleHandle(TEXT("kernel32")), "IsWow64Process");

    if (NULL != fnIsWow64Process)
    {
        if (!fnIsWow64Process(hProc, &bIsWow64))
        {
            //handle error
        }
    }
    return bIsWow64;
}

int main(int argc, char* argv[])
{

#ifdef _WIN64
    HANDLE hProc = GetCurrentProcess(); // or OpenProcess(...);
    if(IsWow64(hProc))
    {
         std::cout << "Программа запущена на х86, но скомпилирована на х64" << std::endl;
    }
    else
    {
         std::cout << "Программа запущена на х64, и скомпилирована на х64" << std::endl;
    }
#else
        std::cout << "Программа запущена на х86, и скомпилирована на х86" << std::endl;
#endif

    return 0;
}
