#include <iostream>
#include <Windows.h>

int main()
{
  HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
  int value;
  
  ReadProcessMemory(hProc, (LPCVOID) 0x123456, &value, sizeof(value), NULL);
  value += 100;
  WriteProcessMemory(hProc, (LPVOID) 0x123456, &value, sizeof(value), NULL);
  
  CloseHandle(hProc);
  return 0;
}
