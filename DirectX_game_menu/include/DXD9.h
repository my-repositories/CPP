/*
CREDITS
Grab from UnknownCheats.me - All this source code
TastyHorror from UnknownCheats.me and GuidedHacking.com - Writing comments and editing the code slightly
*/

#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>

/*
#pragma comment(lib, libname) tells the linker to add the 'libname' library to the list of library dependencies, as if you had added it in the project properties at Linker->Input->Additional dependencies.
*/
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")

IDirect3DDevice9Ex* retDXDEVICE();
int D3DIniti(HWND hWnd);
void DrawFilled(int x, int y, int w, int h, int r, int g, int b, int a);
void DrawBorder(int x, int y, int w, int h, int px, int r, int g, int b, int a);
int Draw_Text(char* String, int x, int y, int r, int g, int b, int a);
