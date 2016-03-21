#include "Window.h"
#include <Windows.h>
#include "Input.h"
#include "Glew.h"
#include "Renderer.h"

// Prototypes
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration for WndProc

// Static init
uint32 VWindow::Count = 0;
VWindow* VWindow::CurrentContext = nullptr;

// Non-public abi structs
struct NativeWindow_t
{
	HGLRC	hRC = nullptr;		// Rendering context
	HDC		hDC = nullptr;		// Private GDI Device Context
	HWND	hWnd = nullptr;		// Window handle
	HINSTANCE	hInstance;		// Instance of the application

#ifdef GLEW_MX
	GLEWContext* glewContext;
#endif
	NativeWindow_t()
		: hRC(nullptr),
		hDC(nullptr),
		hWnd(nullptr),
		hInstance(nullptr)
#ifdef GLEW_MX
		, glewContext(nullptr)
#endif
	{}
};


#ifdef GLEW_MX
GLEWContext* glewGetContext()
{
	return VWindow::CurrentContext->GetNativeWindow()->glewContext;
}
#endif

// ------------------------------------ VWindow -------------------------------------
VWindow::VWindow(uint32 width, uint32 height, const char* title, EWindowMode mode, VWindow* parent)
	:WindowID(++Count),
	NativeWindow(nullptr),
	UserData(nullptr),
	Input(nullptr)
{
	if (CreateNewWindow(width, height, title, mode, parent))
	{
		Input = new VInput();
	}
}

VWindow::~VWindow()
{
	Close();
	if (Input) delete(Input);
}

bool VWindow::CreateNewWindow(uint32 width, uint32 height, const char* title = "Default Window", EWindowMode mode = WINDOW_DEFAULT, VWindow* parent = nullptr)
{
	// Create NativeWindow ptr
	if (NativeWindow != nullptr)
		Close();

	NativeWindow = new NativeWindow_t();

#ifdef GLEW_MX
	NativeWindow->glewContext = nullptr;
	VWindow* PreviousContext = CurrentContext;
#endif

	unsigned int PixelFormat;		// Holds the result of the chosen pixel format

	WNDCLASS wc;		// Window class structure

	DWORD dwExStyle;	// Window Extended Style
	DWORD dwStyle;		// Window Style

	RECT WindowRect;                        // Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;              // Set Left Value To 0
	WindowRect.right = (long)width;         // Set Right Value To Requested Width
	WindowRect.top = (long)0;               // Set Top Value To 0
	WindowRect.bottom = (long)height;       // Set Bottom Value To Requested Height

	bool fullscreen = (mode == WINDOW_FULLSCREEN_BORDERLESS);             // Set The Global Fullscreen Flag

	NativeWindow->hInstance = GetModuleHandle(NULL);	// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// Redraw On Move, And Own DC For Window
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = NativeWindow->hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);				// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;							// No Background Required For GL
	wc.lpszMenuName = NULL;								// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";						// Set The Class Name
	
	if (!RegisterClass(&wc))							// Attempt To Register The Window Class
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
		dmScreenSettings.dmBitsPerPel = 8;					// Selected Bits Per Pixel
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

	if (!(NativeWindow->hWnd = CreateWindowEx(dwExStyle,      // Extended Style For The Window
		"OpenGL",									// Class Name
		title,										// Window Title
		WS_CLIPSIBLINGS |							// Required Window Style
		WS_CLIPCHILDREN |							// Required Window Style
		dwStyle,									// Selected Window Style
		0, 0,										// Window Position
		WindowRect.right - WindowRect.left,			// Calculate Adjusted Window Width
		WindowRect.bottom - WindowRect.top,			// Calculate Adjusted Window Height
		parent != nullptr ? parent->NativeWindow->hWnd : NULL,		// No Parent Window
		NULL,										// No Menu
		NativeWindow->hInstance,					// Instance
		(LPVOID)this)))									// Pass this ptr To WM_CREATE
	{
		Close();							// Reset The Display
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
		8,									// Select Our Color Depth
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

	if (!(NativeWindow->hDC = GetDC(NativeWindow->hWnd)))                   // Did We Get A Device Context?
	{
		Close();                         // Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;							// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(NativeWindow->hDC, &pfd)))      // Did Windows Find A Matching Pixel Format?
	{
		Close();                         // Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                           // Return FALSE
	}

	if (!SetPixelFormat(NativeWindow->hDC, PixelFormat, &pfd))               // Are We Able To Set The Pixel Format?
	{
		Close();                         // Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                           // Return FALSE
	}

	if (!(NativeWindow->hRC = wglCreateContext(NativeWindow->hDC)))                   // Are We Able To Get A Rendering Context?
	{
		Close();                         // Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                           // Return FALSE
	}

	if (!wglMakeCurrent(NativeWindow->hDC, NativeWindow->hRC))                        // Try To Activate The Rendering Context
	{
		Close();                         // Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                           // Return FALSE
	}

	// Make this current before init glew
	VWindow* previousContext = VWindow::CurrentContext;
	MakeCurrent();

	NativeWindow->glewContext = new GLEWContext();
	glewContextInit(NativeWindow->glewContext);
	if (glewInit() != GLEW_OK)
	{
		Close();
		MessageBox(NULL, "Cannot initialize Glew", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                           // Return FALSE
	}

	ShowWindow(NativeWindow->hWnd, SW_SHOW);                       // Show The Window
	SetForegroundWindow(NativeWindow->hWnd);                      // Slightly Higher Priority
	SetFocus(NativeWindow->hWnd);                             // Sets Keyboard Focus To The Window
												//ReSizeGLScene(width, height);                       // Set Up Our Perspective GL Screen
	// Restore previous context
	MakeCurrent(previousContext);

	return true;
}

void VWindow::Close()	// Called when window should be teard down
{
	if (!NativeWindow) return;

	//if (fullscreen)		// Is window full screen - make sure cursor is shown
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

	if (NativeWindow->hRC)	// Do we have a rendering context?
	{
		if (!wglMakeCurrent(NULL, NULL))	// Are we able to release the DC and RC contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(NativeWindow->hRC))		// Are we able to delete the RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
	}

	if (NativeWindow->hDC && !ReleaseDC(NativeWindow->hWnd, NativeWindow->hDC))	// try releasing the DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
	}

	if (NativeWindow->hWnd && !DestroyWindow(NativeWindow->hWnd))   // Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
	}

	if (!UnregisterClass("OpenGL", NativeWindow->hInstance))	// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
	}

	delete(NativeWindow);
	NativeWindow = nullptr;
}

void VWindow::MakeCurrent(VWindow* ctx)
{
	if (ctx != nullptr)
	{
		ctx->MakeCurrent();
	}
}

void VWindow::MakeCurrent()
{
	wglMakeCurrent(NativeWindow->hDC, NativeWindow->hRC);
	CurrentContext = this;

	VRenderer::GetInstance()->SetContextID(WindowID - 1);
	Input->MakeCurrentContext();
}


void VWindow::SetPosition(int xPos, int yPos)
{

}

bool VWindow::ShouldClose()
{
	return false;
}

void VWindow::SignalShouldClose()
{

}

void VWindow::Swapbuffers()
{
	SwapBuffers(NativeWindow->hDC);
}

void VWindow::PollEvents()
{
	MSG msg;

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);             // Translate The Message
		DispatchMessage(&msg);              // Dispatch The Message
	}
}

void VWindow::TerminateAll()
{

}

void VWindow::GetWindowSize(int* width, int* height)
{

}

void VWindow::GetFrameBufferSize(int* width, int* height)
{

}

void VWindow::GetPrimaryMonitorSize(int* width, int* height)
{

}

void VWindow::SetBorderHint(bool show)
{

}







// ------------------------- Wnd proc --------------------------------
void KeyAction(VWindow* win, WPARAM key, bool down)
{
	EKeyCode code;
	switch (key)
	{
		// Numberical keys
	case '0': code = (EKeyCode)'0'; break;
	case '1': code = (EKeyCode)'1'; break;
	case '2': code = (EKeyCode)'2'; break;
	case '3': code = (EKeyCode)'3'; break;
	case '4': code = (EKeyCode)'4'; break;
	case '5': code = (EKeyCode)'5'; break;
	case '6': code = (EKeyCode)'6'; break;
	case '7': code = (EKeyCode)'7'; break;
	case '8': code = (EKeyCode)'8'; break;
	case '9': code = (EKeyCode)'9'; break;

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
		win->GetInput()->SetKeyDown(code);
	else
		win->GetInput()->SetKeyUp(code);

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM  wParam, LPARAM  lParam)                 // Additional Message Information
{
	VWindow* pThis = (VWindow*)GetWindowLongPtr(hWnd, GWL_USERDATA);

	switch (uMsg)                               // Check For Windows Messages
	{
	case WM_NCCREATE:
	{
		// Set 'this' VWindow pointer
		SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)((CREATESTRUCT*)lParam)->lpCreateParams);
		SetWindowPos(hWnd, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
	
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	case WM_ACTIVATE:                       // Watch For Window Activate Message
	{
		//if (!HIWORD(wParam))                    // Check Minimization State
		//{
		//	active = true;                    // Program Is Active
		//}
		//else
		//{
		//	active = false;                   // Program Is No Longer Active
		//}

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
		KeyAction(pThis, wParam, true);                    // If So, Mark It As TRUE
		return 0;                       // Jump Back
	}

	case WM_KEYUP:                          // Has A Key Been Released?
	{
		KeyAction(pThis, wParam, false);                   // If So, Mark It As FALSE
		return 0;                       // Jump Back
	}

	case WM_MOUSEMOVE:		// Mouse moves over the context
	{
		uint32 x = LOWORD(lParam);
		uint32 y = HIWORD(lParam);

		pThis->GetInput()->SetMousePosition(Vector2f((float)x, (float)y));

		return 0;
	}

	case WM_LBUTTONDOWN:		// Left button down
	{
		pThis->GetInput()->SetMouseButtonDown(0);
		return 0;
	}

	case WM_RBUTTONDOWN:		// Right button down
	{
		pThis->GetInput()->SetMouseButtonDown(1);
		return 0;
	}
	case WM_MBUTTONDOWN:		// Middle button down
	{
		pThis->GetInput()->SetMouseButtonDown(2);
		return 0;
	}
	case WM_LBUTTONUP:			// Left button Up
	{
		pThis->GetInput()->SetMouseButtonUp(0);
		return 0;
	}
	case WM_RBUTTONUP:			// Right button up
	{
		pThis->GetInput()->SetMouseButtonUp(1);
		return 0;
	}
	case WM_MBUTTONUP:			// Middle button up
	{
		pThis->GetInput()->SetMouseButtonUp(2);
		return 0;
	}
	case WM_LBUTTONDBLCLK:		// Left button dbl click
	{
		pThis->GetInput()->SetMouseButtonDblClick(0);
		return 0;
	}
	case WM_RBUTTONDBLCLK:		// Right button dbl click
	{
		pThis->GetInput()->SetMouseButtonDblClick(1);
		return 0;
	}
	case WM_MBUTTONDBLCLK:		// Middle button dbl click
	{
		pThis->GetInput()->SetMouseButtonDblClick(2);
		return 0;
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
