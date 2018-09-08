/*
CREDITS
Grab from UnknownCheats.me - All this source code
TastyHorror from UnknownCheats.me and GuidedHacking.com - Writing comments and editing the code slightly
*/

#include "menu.h"

/*
Some of our global variables for our menu.
*/
char menuItems[6][32] = { "ITEM 1", "ITEM 2", "ITEM 3", "ITEM 4", "ITEM 5", "ITEM 6" };
int cX = 10, cY = 40, incY = 40;


/*
Function that we use to draw.
*/
int RenderIt(IDirect3DDevice9Ex* dx_Device, bool ShowMenu, int maxItems, int selectedItem)
{
	/*
	0 (DWORD) is count, which is the number of rectanges in the array at pRects.
	0 (D3DRECT) is pRects which is the pointer to an array of D3DRECT struct.
	D3DCLEAR_TARGET (DWORD) clears a render target, or all targets in a multiple render target.
	0 (D3DCOLOR) clears a render target to this ARGB color.
	1.0f (float) is clearing the depth buffer to this new z value which ranges from 0 to 1.
	0 (DWORD) clears the stencil buffer to this new value which ranges from 0 to 2n-1 (n= bit depth of the stencil buffer)

	Basically this just clears the device.
	*/
	dx_Device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);

	/*
	Begins a scene. BeginScene causes the system to check its internal data structures and the availability and validity of rendering surfaces. It also sets an internal flag to signal that a scene is in progress. After you begin a scene, you can call the various rendering methods to render the primitives or individual vertices that make up the objects in the scene. Attempts to call rendering methods when a scene is not in progress fail.
	*/
	dx_Device->BeginScene();

	/*
	Drawing our menu.
	*/
	if (ShowMenu)
	{
		for (size_t i = 0; i < maxItems; i++)
		{
			DrawBorder(cX, cY, 150, 30, 2, 0, 0, 0, 240);
			if (selectedItem == i)
			{
				DrawFilled(cX + 2, cY, 148, 28, 40, 200, 40, 240);
			}
			else
			{
				DrawFilled(cX + 2, cY, 148, 28, 70, 70, 70, 240);
			}
			Draw_Text(menuItems[i], cX + 8, cY + 4, 255, 255, 255, 255);
			cY += incY;
		}
		cX = 10; 
		cY = 40;
	}
	/*
	Ends a scene that was begun. The EndScene method flushes cached data, verifies the integrity of rendering surfaces, and clears an internal flag that signals when a scene is in progress.

	*/
	dx_Device->EndScene();
	/*
	Swap the swapchain's next buffer with the front buffer. What does this mean? Well TBH all I understand is that it swaps the devices buffer to a cleared out buffer. Please correct me If I am wrong.
	*/
	dx_Device->PresentEx(NULL, NULL, NULL, NULL, NULL);

	return 0;
}

