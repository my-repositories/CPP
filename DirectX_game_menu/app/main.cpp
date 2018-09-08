/*
CREDITS
Grab from UnknownCheats.me - All this source code
TastyHorror from UnknownCheats.me and GuidedHacking.com - Writing comments and editing the code slightly
*/

#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <dwmapi.h>
#include "DXD9.h"
#include "menu.h"

/*
#pragma comment(lib, libname) tells the linker to add the 'libname' library to the list of library dependencies, as if you had added it in the project properties at Linker->Input->Additional dependencies.
*/
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dwmapi.lib")

/*
Global Variables that are required.
*/
int Width = 800, Height = 600;
HWND hWnd, TargetWnd;
MSG Message;
RECT TargetRect, CheckWnd;

/*
This is the window size basically. We need to pass this when we are painting. Don't worry, we will repaint to the correct locations and sizes.
*/
const MARGINS Margin = { 0,	0, Width, Height };

/*
LRESULT is a datatype. Callback is a function pointer that is called everytime a certain condition is met. 
*/
LRESULT CALLBACK Proc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
		/*
		If we get a msg that says to paint. Basically we always paint, well want to anyways.
		*/
	case WM_PAINT:
		/*
		DwmExtendFrameIntoClientArea extends the window frame into the client area.
		*/
		return DwmExtendFrameIntoClientArea(hWnd, &Margin);
		/*
		If we get a msg that says to destory. Basically if overlay closes, we do this.
		*/
	case WM_DESTROY:
		/*
		We need to use PostQuitMessage to exit a message loop.
		*/
		PostQuitMessage(0);
		break;
	default:
		/*
		Calls the default window procedure to provide default processing for any window messages that an application does not process. This function ensures that every message is processed. DefWindowProc is called with the same parameters received by the window procedure.
		*/
		return DefWindowProc(hWnd, Message, wParam, lParam);
	}

	return 0;
}

/*
Every win32 based app must have a winmain function. Just like in any other C/C++ program we need int main().
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR CmdLine, int CmdShow)
{

	/*
	OverlayWnd (WNDCLASSEX) contains window class information. 
	*/
	WNDCLASSEX OverlayWnd;

	/*
	cbSize (UINT) is the size, in bytes, of this structure.
	*/
	OverlayWnd.cbSize = sizeof(WNDCLASSEX);

	/*
	style (UINT) is the style, in this case it will redraw the entire window if a movement or size adjustment changes the width of the client area.
	*/
	OverlayWnd.style = CS_HREDRAW | CS_VREDRAW;

	/*
	lpfnWndProc (WNDPROC) is a pointer to the window procedure.
	*/
	OverlayWnd.lpfnWndProc = Proc;

	/*
	cbClsExtra (INT) and cbWndExtra (INT) are both num of extra bytes to allocate following the window-class structure and window instance. Is this important for you atm? No.
	*/
	OverlayWnd.cbClsExtra = 0;
	OverlayWnd.cbWndExtra = 0;

	/*
	hInstance (HINSTANCE) is a handle to the instance that contains the window procedure for the class.
	*/
	OverlayWnd.hInstance = hInstance;

	/*
	hIcon (HICON) is a handle to the class icon.
	*/
	OverlayWnd.hIcon = LoadIcon(0, IDI_APPLICATION);

	/*
	hCursor (HCURSOR) is a handle to the class cursor.
	*/
	OverlayWnd.hCursor = LoadCursor(0, IDC_ARROW);

	/*
	hbrBackground (HBRUSH) is a handle to the class background brush.
	*/
	OverlayWnd.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));

	/*
	lpszMenuName (LPCTSTR) is a pointer to a null-terminated char string that specifies the resource name of the class menu, as the name appears in the resource file.
	*/
	OverlayWnd.lpszMenuName = "Overlay";

	/*
	lpszClassName (LPCTSTR) is a pointer to a null-terminated string or is an atom.
	*/
	OverlayWnd.lpszClassName = "Overlay";
	
	/*
	hIconSm (HICON) is a handle to a small icon that is associated with the window class. 
	*/
	OverlayWnd.hIconSm = LoadIcon(0, IDI_APPLICATION);

	/*
	RegisterClassEx registers a window class for subsequent use in calls to the CreateWindow or CreateWindowEx function. If it fails the app exits.
	*/
	if (!RegisterClassEx(&OverlayWnd))
	{
		exit(1);
	}

	/*
	CreateWindowEx creates an overlapped, pop-up, or child window with an extended window style.

	dwExStyle (DWORD) is the extended window style of the window being created.
	WS_EX_TOPMOST means that the window should be placed above all non-topmost windows and should stay above them, even when the window is deactivated
	WS_EX_LAYERED uses a layered window can significantly improve performance and visual effects for a window that has a complex shape, animates its shape, or wishes to use alpha blending effects.
	WS_EX_COMPOSITED paints all descendants of a window in bottom-to-top painting order using double-buffering.
	WS_EX_TRANSPARENT means that the window should not be painted until siblings beneath the window (that were created by the same thread) have been painted.

	lpClassName (LPCTSTR) is a null-terminated string or a class atom created by a previous call to the RegisterClass or RegisterClassEx function.
	lpWindowName (LPCSTR) is the window name.
	dwStyle (DWORD) is the style of the window being created.  
	WS_POPUP means that the window is a pop-up window.
	x (int) is the horizontal position of the window.
	y (int) is the vertical position of the window.
	nWidth (int) is the width.
	nHeight (int) is the height.

	The last three nulls are all optional, and I wont bother mentioning them. If you are interested google CreateWindowEx.
	*/
	hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_COMPOSITED | WS_EX_TRANSPARENT, "Overlay", "Overlay", WS_EX_TOPMOST | WS_POPUP, 100, 100, 1024, 786, NULL, NULL, NULL, NULL);

	/*
	SetLayeredWindowAttributes sets the opacity and transparency color key for a layered window.
	*/
	SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
	SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);

	/*
	Show the layered window aka our overlay.
	*/
	ShowWindow(hWnd, SW_SHOW);

	/*
	We use our handle to our overlay and initalize our D3D adapter.
	*/
	D3DIniti(hWnd);
	int maxItems = 6;
	int selectedItem = 0;
	bool ShowMenu = true;
	while (1)
	{

		if (GetAsyncKeyState(VK_INSERT))
		{
			ShowMenu = !ShowMenu;
			Sleep(100);
		}

		if (GetAsyncKeyState(VK_UP) & 1)
		{
			if (selectedItem > 0) { selectedItem--; }
		}

		if (GetAsyncKeyState(VK_DOWN) & 1)
		{ 
			if (selectedItem < (maxItems - 1)) { selectedItem++; }
		}

		/*
		Dispatches incoming sent messages, checks the thread message queue for a posted message, and retrieves the message (if any exist). Messages are removed from the queue after processing due to PM_REMOVE.
		*/
		if (PeekMessage(&Message, hWnd, 0, 0, PM_REMOVE))
		{
			/*
			Translates virtual-key messages into character messages.
			*/
			TranslateMessage(&Message);

			/*
			Dispatches a message to a window procedure.
			*/
			DispatchMessage(&Message);
		}

		/*
		Get target window.
		*/
		TargetWnd = FindWindow(0, "World of Warcraft");
		/*
		Set the RECT using the targeted window.
		*/
		GetWindowRect(TargetWnd, &TargetRect);
		/*
		Resize the overlay matching what is required.
		*/
		MoveWindow(hWnd, TargetRect.left, TargetRect.top, TargetRect.right - TargetRect.left, TargetRect.bottom - TargetRect.top, true);

		/*
		If there is no game, quit.
		*/
		if (!TargetWnd)
		{
			exit(0);
		}

		/*
		Let us draw on the overlay.
		*/
		RenderIt(retDXDEVICE(), ShowMenu, maxItems, selectedItem);
	}
	return 0;
}