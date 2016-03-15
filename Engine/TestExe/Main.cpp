#include <Windows.h>

// Tut : http://nehe.gamedev.net/tutorial/creating_an_opengl_window_%28win32%29/13001/

HGLRC	hRC = nullptr;		// Rendering context
HDC		hDC = nullptr;		// Private GDI Device Context
HWND	hWnd = nullptr;		// Window handle
HINSTANCE	hInstance;		// Instance of the application

bool keys[256];				// Array of keys being pressed
bool active = true;			// Window active flag
bool fullscreen = false;	// Fullscreen flag

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration for WndProc

void KillWindow()	// Called when window should be teard down
{
	if (fullscreen)		// Is window full screen - make sure cursor is shown
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

	if (hRC)	// Do we have a rendering context?
	{
		if (!wglMakeCurrent(NULL, NULL))	// Are we able to release the DC and RC contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))		// Are we able to delete the RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = nullptr;
	}

	if (hDC && !ReleaseDC(hWnd, hDC))	// try releasing the DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = nullptr;                  
	}

	if (hWnd && !DestroyWindow(hWnd))   // Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = nullptr;                          
	}
}

bool CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	unsigned int PixelFormat;		// Holds the result of the chosen pixel format

	WNDCLASS wc;		// Window class structure

	DWORD dwExStyle;	// Window Extended Style
	DWORD dwStyle;		// Window Style

	RECT WindowRect;                        // Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;              // Set Left Value To 0
	WindowRect.right = (long)width;         // Set Right Value To Requested Width
	WindowRect.top = (long)0;               // Set Top Value To 0
	WindowRect.bottom = (long)height;       // Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;             // Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;  // Redraw On Move, And Own DC For Window
	wc.lpfnWndProc = (WNDPROC)WndProc;              // WndProc Handles Messages
	wc.cbClsExtra = 0;								// No Extra Window Data
	wc.cbWndExtra = 0;								// No Extra Window Data
	wc.hInstance = hInstance;						// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);         // Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);       // Load The Arrow Pointer
	wc.hbrBackground = NULL;						// No Background Required For GL
	wc.lpszMenuName = NULL;							// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";					// Set The Class Name

	if (!RegisterClass(&wc))                        // Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                        
	}

	if (fullscreen)
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings)); // Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);     // Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;					// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;					// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Run In A Window.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = false;
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return false;                   // Exit And Return FALSE
			}
		}
	}

	if (fullscreen)                             // Are We Still In Fullscreen Mode?
	{

	}
}