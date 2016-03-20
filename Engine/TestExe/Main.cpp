#include <Windows.h>
#include <stdio.h>
#include "Input.h"
#include "Engine.h"
#include "Renderer.h"
#include "FilePath.h"
#include "Environment.h"
#include "MathLib.h"

// Tut : http://nehe.gamedev.net/tutorial/creating_an_opengl_window_%28win32%29/13001/

HGLRC	hRC = nullptr;		// Rendering context
HDC		hDC = nullptr;		// Private GDI Device Context
HWND	hWnd = nullptr;		// Window handle
HINSTANCE	hInstance;		// Instance of the application

bool keys[MAX_KEYCOUNT];				// Array of keys being pressed
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

	return true;
}

void KeyAction(WPARAM key, bool down)
{
	EKeyCode code;
	switch (key)
	{
		// Numberical keys
		case '0' : code = (EKeyCode)'0'; break;
		case '1' : code = (EKeyCode)'1'; break;
		case '2' : code = (EKeyCode)'2'; break;
		case '3' : code = (EKeyCode)'3'; break;
		case '4' : code = (EKeyCode)'4'; break;
		case '5' : code = (EKeyCode)'5'; break;
		case '6' : code = (EKeyCode)'6'; break;
		case '7' : code = (EKeyCode)'7'; break;
		case '8' : code = (EKeyCode)'8'; break;
		case '9' : code = (EKeyCode)'9'; break;

		// Letters
		case 'A': code = (EKeyCode)'A'; break;
		case 'B': code = (EKeyCode)'B'; break;
		case 'C': code = (EKeyCode)'C'; break;
		case 'D': code = (EKeyCode)'D'; break;
		case 'E': code = (EKeyCode)'E'; break;
		case 'F': code = (EKeyCode)'F'; break;
		case 'G': code = (EKeyCode)'G'; break;
		case 'H': code = (EKeyCode)'H'; break;
		case 'I': code = (EKeyCode)'I'; break;
		case 'J': code = (EKeyCode)'J'; break;
		case 'K': code = (EKeyCode)'K'; break;
		case 'L': code = (EKeyCode)'L'; break;
		case 'M': code = (EKeyCode)'M'; break;
		case 'N': code = (EKeyCode)'N'; break;
		case 'O': code = (EKeyCode)'O'; break;
		case 'P': code = (EKeyCode)'P'; break;
		case 'Q': code = (EKeyCode)'Q'; break;
		case 'R': code = (EKeyCode)'R'; break;
		case 'S': code = (EKeyCode)'S'; break;
		case 'T': code = (EKeyCode)'T'; break;
		case 'U': code = (EKeyCode)'U'; break;
		case 'V': code = (EKeyCode)'V'; break;
		case 'W': code = (EKeyCode)'W'; break;
		case 'X': code = (EKeyCode)'X'; break;
		case 'Y': code = (EKeyCode)'Y'; break;
		case 'Z': code = (EKeyCode)'Z'; break;

		// Function keys
		case VK_F1:	 code = KEY_F1; break;
		case VK_F2:	 code = KEY_F2; break;
		case VK_F3:	 code = KEY_F3; break;
		case VK_F4:	 code = KEY_F4; break;
		case VK_F5:	 code = KEY_F5; break;
		case VK_F6:	 code = KEY_F6; break;
		case VK_F7:	 code = KEY_F7; break;
		case VK_F8:	 code = KEY_F8; break;
		case VK_F9:	 code = KEY_F9; break;
		case VK_F10: code = KEY_F10; break;
		case VK_F11: code = KEY_F11; break;
		case VK_F12: code = KEY_F12; break;

		// Special keys
		case VK_ESCAPE:		code = KEY_ESC; break;
		case VK_SHIFT:		code = KEY_SHIFT; break;
		case VK_TAB:		code = KEY_TAB; break;
		case VK_MENU:		code = KEY_ALT; break;
		case VK_CONTROL:	code = KEY_CTRL; break;
		case VK_CAPITAL:	code = KEY_CAPSLOCK; break;
		case VK_NUMLOCK:	code = KEY_NUMLOCK; break;
		case VK_SPACE:		code = KEY_SPACEBAR; break;
		case VK_RETURN:		code = KEY_RETURN; break;
		case VK_BACK:		code = KEY_BACKSPACE; break;
		case VK_DELETE:		code = KEY_DELETE; break;
		case VK_HOME:		code = KEY_HOME; break;

		// Unkown
		default:	code = KEY_UNKNOWN; break;
	}

	if (down)
		VInput::GetInstance()->SetKeyDown(code);
	else
		VInput::GetInstance()->SetKeyUp(code);

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM  wParam, LPARAM  lParam)                 // Additional Message Information
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
		KeyAction(wParam, true);                    // If So, Mark It As TRUE
		return 0;                       // Jump Back
	}

	case WM_KEYUP:                          // Has A Key Been Released?
	{
		KeyAction(wParam, false);                   // If So, Mark It As FALSE
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

void Test()
{
	Vector3f v1(1, 2, 3);
	Vector4f v2(1, 2, 3, 4);

	Quaternion q;
	Quaternion q1(1, 2, 3, 4);
	Quaternion q2 = v1;
	Quaternion q3 = v2;


	q1.Normalize();
	q2.Normalize();

	float d = q1.Dot(q2);

	Quaternion rot = Quaternion::EulerAngles(0, 90, 0);
	
	Matrix3f m3 = rot;
	Matrix4f m4 = rot;


}

// Main
int main(int argc, char** argv)
{
	MSG msg;                                // Windows Message Structure
	bool done = FALSE;                         // Bool Variable To Exit Loop

	// Create Our OpenGL Window
	if (!CreateGLWindow("Vici Editor", 640, 480, 16, fullscreen))
	{
		return 0;                           // Quit If Window Was Not Created
	}

	// Setup stuff
	VString vpath = VEnvironment::GetSystemEnvVar("VICI_HOME");
	VFilePath vResPath = vpath + "Resources/";

	printf("Res = %s\n", (char*)vResPath);
	VEnvironment::GetInstance()->Put(ItemToString(FILE_EDITOR_DIRECTORY), vpath.c_str());
	VEnvironment::GetInstance()->Put(ItemToString(FILE_EDITOR_RESOURCE_DIRECTORY), vResPath);

	VEngine* vici = new VEngine();
	vici->Init(0, nullptr);

	Test();

	uint32 frame = 0;

	while (!done)
	{
		// Per frame init
		frame++;
		VInput::GetInstance()->SetCurrentFrame(frame);

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
					vici->Update();
					vici->Render();

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

		if (VInput::GetInstance()->KeyDown(KEY_4))
			printf("4 pressed\n");
	}

	// Shutdown
	KillWindow();                             // Kill The Window
	return (msg.wParam);                            // Exit The Program
}