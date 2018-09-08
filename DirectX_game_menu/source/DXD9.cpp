/*
CREDITS
Grab from UnknownCheats.me - All this source code
TastyHorror from UnknownCheats.me and GuidedHacking.com - Writing comments and editing the code slightly
*/

#include "DXD9.h"

/*
Applications use the methods of the IDirect3D9Ex interface (which inherits from IDirect3D9) to create Microsoft Direct3D 9Ex objects and set up the environment. This interface includes methods for enumerating and retrieving capabilities of the device and is available when the underlying device implementation is compliant with Windows Vista.
*/
IDirect3D9Ex* dx_Object = NULL;

/*
Applications use the methods of the IDirect3DDevice9Ex interface to render primitives, create resources, work with system-level variables, adjust gamma ramp levels, work with palettes, and create shaders. The IDirect3DDevice9Ex interface derives from the IDirect3DDevice9 interface.
*/
IDirect3DDevice9Ex* dx_Device = NULL;

/*
Describes the presentation parameters.
*/
D3DPRESENT_PARAMETERS dx_Param;

/*
The ID3DXFont interface encapsulates the textures and resources needed to render a specific font on a specific device.
*/
ID3DXFont* dx_Font = 0;

IDirect3DDevice9Ex* retDXDEVICE()
{
	return dx_Device;
}

/*
We require to initialize the D3D drawing, so we require hWnd. Windows identifies each form or application by assigning it a handle or also known as hWnd.
*/
int D3DIniti(HWND hWnd)
{
	/*
	We need to check to see if we can create an IDirect3D9Ex object and return an interface to it. Why is D3D_SDK_VERSION passed? Because we will need to ensure that the header files used in the compiled application match the version of the installed runtime DLLs. Why are we passing the object to dx_Object? Because we are creating an IDirect3D9Ex object, and we need to store it somewhere. If it fails, the app crashes (the DLL), and if it passes, it continues, simple huh?
	*/
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &dx_Object)))
	{
		exit(1);
	}

	/*
	We created the dx_Param earlier, it is a D3DPRESENT_PARAMETERS structure. It contains many variables you can modify but in this source we are only modifying these variables.

	BackBufferFormat (D3DFORMAT) is the buffer that is drawn off-screen and will be switched with the front buffer at the next frame. This is considered double buffering, which is what you need to do in GDI to ensure that it does not flicker. But GDI will still flicker because it is "slow" you could persay.

	D3DFMT_A8R8G8B8	(Value: 21) is an 32-bit ARGB pixel format with alpha, using 8 bits per channel.
	*/
	dx_Param.BackBufferFormat = D3DFMT_A8R8G8B8;

	/*
	hDeviceWindow (HWND) is the form or application that determines the location and size of the back buffer on the screen.
	*/
	dx_Param.hDeviceWindow = hWnd;

	/*
	MultiSampleQuality (DWORD) is the quality level. Technically speaking DEFAULT_QUALITY is zero which also is kind of funny because zero is the lowest MultiSampleQuality. Why are we setting this? Well this is all GPU related, and microsoft is extremely vauge about this, so we will just leave this as zero.
	*/
	dx_Param.MultiSampleQuality = DEFAULT_QUALITY;

	/*
	SwapEffect (D3DSWAPEFFECT) is how the front and back buffer are to be swapped. When we disregard this, we can do multi sampling (above).
	*/
	dx_Param.SwapEffect = D3DSWAPEFFECT_DISCARD;

	/*
	Windowed (BOOL) is basically asking you if the form or application is running windowed or fullscreen. True is windowed. False is fullscreen.
	*/
	dx_Param.Windowed = true;

	/*
	We need to see if we can create a device to REPRESENT the display adapter.
	D3DADAPTER_DEFAULT (UNIT) is the always the primary display adapter.
	D3DDEVTYPE_HAL (D3DDEVTYPE) (value: 1) is hardware rasterization. Shading is done with software, hardware, or mixed transform and lighting.
	hWnd (HWND) is the form we will create the device in mind with. Something I noticed was that this can be null if we set the hDeviceWindow to a non-null value, which it is. So I changed it to a null.
	D3DCREATE_HARDWARE_VERTEXPROCESSING (DWORD) specifies hardware vertex processing.
	dx_Param (D3DPRESENT_PARAMTERS*) describe the presentation parameters for the device to be created.
	0 (D3DDISPLAYMODEEX*) is only used when the device is set to fullscreen, which it is not for this source, but it basically is the properties of a display mode (size, width, height, refresh rate, format, scanlineordering).
	dx_Device (IDirect3DDevice9Ex**) is the address of a pointer to the returned IDirect3DDevice9Ex, which represents the created device.
	*/
	if (FAILED(dx_Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, NULL, D3DCREATE_HARDWARE_VERTEXPROCESSING, &dx_Param, 0, &dx_Device)))
	{
		exit(1);
	}

	/*
	D3DXCreateFont creates a font object for a device and font.

	D3DXCreateFont(device, h, w, weight, miplevels, italic, charset, OutputPrecision, quality, pitchandfamily, pfaceanme, *ppfont)

	dx_Device (LPDIRECT3DDEVICE9) is the device we will be creating a font for.
	24 (INT) is the height of the characters in logical units.
	0 (UINT) is the width of the characters in logical units.
	FW_REGULAR (UNIT) is the typeface weight.
	0 (MipLevels) is the number of mipmap levels. MipMaps (not miplevels) are pre-calculated, optimized collections of images that accompany a main texture, intended to increase rendering speed and reduce aliasing artifacts
	false (BOOL) is if the italic font is true or not. In this case it is false.
	DEFAULT_CHARSET ( DWORD) is the character set of the font.
	OUT_CHARACTER_PRECIS (DWORD) specifies how Windows should attempt to match the desired font sizes and characteristics with actual fonts. In this case we are not using this feature.
	ANTIALIASED_QUALITY (DWORD) specifies how Windows should match the desired font with a real font. In this case we are always antialiasing if the font supports it and the size of the font is not too small or too large.
	DEFAULT_PITCH (DWORD) is the pitch and family index.
	Verdana (LPCTSTR) is the string containing the typeface name (font style).
	dx_Font (LPD3DXFONT*) returns a pointer to an ID3DXFont interface, representing the created font object.
	*/
	D3DXCreateFont(dx_Device, 24, 0, FW_REGULAR, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, "Arial", &dx_Font);

	return 0;
}


/*
Technically should be referred as a DrawFilledLine.
x and y are coordinates.
w and h are width and height.
rgba are color schemes, r as red, g as green, b as blue, a as alpha.
*/
void DrawFilled(int x, int y, int w, int h, int r, int g, int b, int a)
{
	/*
	When you declare a variable in a function, the static keyword specifies that the variable retains its state between calls to that function. The ID3DXLine interface inherits from the IUnknown interface.
	*/
	static ID3DXLine* pLine;

	/*
	If the variable is not set, we will create a line using the device. No actual drawing is done yet.
	*/
	if (!pLine)
	{
		D3DXCreateLine(dx_Device, &pLine);
	}

	/*
	We now set the width of the line we created.
	*/
	pLine->SetWidth(w);

	/*
	We turn antialias off for the line.
	*/
	pLine->SetAntialias(false);

	/*
	We enable opengl style lines, if we set this to false we enable Direct3D style lines. What does that mean? just what type of api we will use.
	*/
	pLine->SetGLLines(true);

	/*
	D3DXVECTOR2 is a two-component vector including operator overloads and type casts. Basically, two float values x and y.
	*/
	D3DXVECTOR2 vLine[2];

	vLine[0].x = x + w / 2;
	vLine[0].y = y;
	vLine[1].x = x + w / 2;
	vLine[1].y = y + h;

	/*
	Begin prepares a device for drawing lines.
	Draw basically draws a line strip in the screen space, using what line (D3DXVECTOR2), the amount of vertices in the vertex list, and the color.
	End restores the device state to how it was when ID3DXLine::Begin was called.
	*/
	pLine->Begin();
	pLine->Draw(vLine, 2, D3DCOLOR_RGBA(r, g, b, a));
	pLine->End();
}


/*
Technically should be referred as a DrawBorderBox.
x and y are coordinates.
w and h are width and height.
rgba are color schemes, r as red, g as green, b as blue, a as alpha.*/
void DrawBorder(int x, int y, int w, int h, int px, int r, int g, int b, int a)
{
	DrawFilled(x, y - px, w, px, r, g, b, a);  // top
	DrawFilled(x, y + h - px, w + px, px, r, g, b, a); // bottom
	DrawFilled(x, y - px, px, h + px, r, g, b, a);  // left
	DrawFilled(x + w, y - px, px, h + px, r, g, b, a);  // right
}

/*
String input is what we want to display.
x and y are coordinates.
rgb are color scheme, r as red, g as green, b as blue, a as alpha.
*/
int Draw_Text(char* String, int x, int y, int r, int g, int b, int a)
{
	/*
	We need to create a font so we can pass in the DrawTextA function, we don't need left or right, but we need to set them to zero. Left and top are were we want to draw at.
	*/
	RECT Font;
	Font.bottom = 0;
	Font.left = x;
	Font.top = y;
	Font.right = 0;

	/*
	What to write, length of the string, font (aka where on screen we want to draw), DT_NOCLIP is the format we will be using (it is the fastest format), and then the last part is we create a color using rgba and pass it.
	*/
	dx_Font->DrawTextA(0, String, strlen(String), &Font, DT_NOCLIP, D3DCOLOR_ARGB(a, r, g, b));

	return 0;
}
