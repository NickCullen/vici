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

	if (!UnregisterClass("OpenGL", hInstance))	// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;                         // Set hInstance To NULL
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
		dwExStyle = WS_EX_APPWINDOW;        // Window Extended Style
		dwStyle = WS_POPUP;                 // Windows Style
		//ShowCursor(FALSE);                  // Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;           // Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;                    // Windows Style
	}
	
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);     // Adjust Window To True Requested Size

	if (!(hWnd = CreateWindowEx(dwExStyle,      // Extended Style For The Window
		"OpenGL",								// Class Name
		title,									// Window Title
		WS_CLIPSIBLINGS |						// Required Window Style
		WS_CLIPCHILDREN |						// Required Window Style
		dwStyle,								// Selected Window Style
		0, 0,									// Window Position
		WindowRect.right - WindowRect.left,		// Calculate Adjusted Window Width
		WindowRect.bottom - WindowRect.top,		// Calculate Adjusted Window Height
		NULL,									// No Parent Window
		NULL,									// No Menu
		hInstance,								// Instance
		NULL)))									// Don't Pass Anything To WM_CREATE
	{
		KillWindow();							// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                           // Return FALSE
	}

	static  PIXELFORMATDESCRIPTOR pfd =		// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),		// Size Of This Pixel Format Descriptor
		1,									// Version Number
		PFD_DRAW_TO_WINDOW |				// Format Must Support Window
		PFD_SUPPORT_OPENGL |				// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,					// Must Support Double Buffering
		PFD_TYPE_RGBA,						// Request An RGBA Format
		bits,								// Select Our Color Depth
		0, 0, 0, 0, 0, 0,					// Color Bits Ignored
		0,									// No Alpha Buffer
		0,									// Shift Bit Ignored
		0,									// No Accumulation Buffer
		0, 0, 0, 0,							// Accumulation Bits Ignored
		16,									// 16Bit Z-Buffer (Depth Buffer)
		0,									// No Stencil Buffer
		0,									// No Auxiliary Buffer
		PFD_MAIN_PLANE,						// Main Drawing Layer
		0,									// Reserved
		0, 0, 0								// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))                   // Did We Get A Device Context?
	{
		KillWindow();                         // Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;							// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))      // Did Windows Find A Matching Pixel Format?
	{
		KillWindow();                         // Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                           // Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))               // Are We Able To Set The Pixel Format?
	{
		KillWindow();                         // Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                           // Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))                   // Are We Able To Get A Rendering Context?
	{
		KillWindow();                         // Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                           // Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))                        // Try To Activate The Rendering Context
	{
		KillWindow();                         // Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                           // Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);                       // Show The Window
	SetForegroundWindow(hWnd);                      // Slightly Higher Priority
	SetFocus(hWnd);                             // Sets Keyboard Focus To The Window
	//ReSizeGLScene(width, height);                       // Set Up Our Perspective GL Screen
}

LRESULT CALLBACK WndProc(HWND    hWnd,                   // Handle For This Window
	UINT    uMsg,                   // Message For This Window
	WPARAM  wParam,                 // Additional Message Information
	LPARAM  lParam)                 // Additional Message Information
{
	switch (uMsg)                               // Check For Windows Messages
	{
	case WM_ACTIVATE:                       // Watch For Window Activate Message
	{
		if (!HIWORD(wParam))                    // Check Minimization State
		{
			active = true;                    // Program Is Active
		}
		else
		{
			active = false;                   // Program Is No Longer Active
		}

		return 0;                       // Return To The Message Loop
	}

	case WM_SYSCOMMAND:                     // Intercept System Commands
	{
		switch (wParam)                     // Check System Calls
		{
		case SC_SCREENSAVE:             // Screensaver Trying To Start?
		case SC_MONITORPOWER:               // Monitor Trying To Enter Powersave?
			return 0;                   // Prevent From Happening
		}
		break;                          // Exit
	}

	case WM_CLOSE:                          // Did We Receive A Close Message?
	{
		PostQuitMessage(0);                 // Send A Quit Message
		return 0;                       // Jump Back
	}

	case WM_KEYDOWN:                        // Is A Key Being Held Down?
	{
		keys[wParam] = TRUE;                    // If So, Mark It As TRUE
		return 0;                       // Jump Back
	}

	case WM_KEYUP:                          // Has A Key Been Released?
	{
		keys[wParam] = FALSE;                   // If So, Mark It As FALSE
		return 0;                       // Jump Back
	}

	case WM_SIZE:                           // Resize The OpenGL Window
	{
		//ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));       // LoWord=Width, HiWord=Height
		return 0;                       // Jump Back
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE   hInstance,              // Instance
	HINSTANCE   hPrevInstance,              // Previous Instance
	LPSTR       lpCmdLine,              // Command Line Parameters
	int     nCmdShow)               // Window Show State
{
	MSG msg;                                // Windows Message Structure
	bool done = FALSE;                         // Bool Variable To Exit Loop

												  // Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL, "Would You Like To Run In Fullscreen Mode?", "Start FullScreen?", MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		fullscreen = true;                       // Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("Vici Editor", 640, 480, 16, fullscreen))
	{
		return 0;                           // Quit If Window Was Not Created
	}

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))           // Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)               // Have We Received A Quit Message?
			{
				done = TRUE;                  // If So done=TRUE
			}
			else                            // If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);             // Translate The Message
				DispatchMessage(&msg);              // Dispatch The Message
			}
		}
		else
		{
			if (active)
			{
				if (keys[VK_ESCAPE])                // Was ESC Pressed?
				{
					done = TRUE;              // ESC Signalled A Quit
				}
				else                        // Not Time To Quit, Update Screen
				{
					//DrawScene();		// Render here
					SwapBuffers(hDC);
				}

				// Toggle fullscreen
				if (keys[VK_F1])                    // Is F1 Being Pressed?
				{
					keys[VK_F1] = FALSE;              // If So Make Key FALSE
					KillWindow();                 // Kill Our Current Window
					fullscreen = !fullscreen;             // Toggle Fullscreen / Windowed Mode
														  // Recreate Our OpenGL Window
					if (!CreateGLWindow("Vici Editor", 640, 480, 16, fullscreen))
					{
						return 0;               // Quit If Window Was Not Created
					}
				}
			}
		}
	}

	// Shutdown
	KillWindow();                             // Kill The Window
	return (msg.wParam);                            // Exit The Program
}