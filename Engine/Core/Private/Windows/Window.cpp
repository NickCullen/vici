#include "Window.h"
#include <Windows.h>
#include "Input.h"
#include "Glew.h"
#include "Renderer.h"

// Prototypes
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration for WndProc

// Static init
bool VWindow::Initialized = false;
uint32 VWindow::Count = 0;
VWindow* VWindow::CurrentContext = nullptr;

// Non-public abi structs
struct NativeWindow_t
{
	HGLRC	hRC = nullptr;		// Rendering context
	HDC		hDC = nullptr;		// Private GDI Device Context
	HWND	hWnd = nullptr;		// Window handle
	HINSTANCE	hInstance;		// Instance of the application
	RECT WindowRect;			// Rect for the window
	DWORD dwExStyle;	// Window Extended Style
	DWORD dwStyle;		// Window Style
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

	~NativeWindow_t()
	{
#ifdef GLEW_MX
		delete(glewContext);
#endif
	}
};


#ifdef GLEW_MX
GLEWContext* glewGetContext()
{
	return VWindow::CurrentContext->GetNativeWindow()->glewContext;
}
#endif

// ------------------------------------ VWindow -------------------------------------
VWindow::VWindow()
	:WindowID(++Count),
	NativeWindow(nullptr),
	UserData(nullptr),
	Input(nullptr),
	Width(500),
	Height(500),
	X(0),
	Y(0),
	Mode(WINDOW_DEFAULT),
	Parent(nullptr),
	Title("My Window"),
	CloseFlag(false),
	FullScreen(false)
{
	if (!Initialized) Initialized = Initialize();

	Input = new VInput();

}

VWindow::~VWindow()
{
	Close();
	if (Input) delete(Input);
}

bool VWindow::Initialize()
{
	WNDCLASS wc;		// Window class structure

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// Redraw On Move, And Own DC For Window
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = GetModuleHandle(NULL);				// Set The Instance
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
	return true;
}

bool VWindow::HandleMode()
{
	FullScreen = Mode == WINDOW_FULLSCREEN_BORDERLESS;

	if (FullScreen)
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings)); // Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);     // Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = Width;					// Selected Screen Width
		dmScreenSettings.dmPelsHeight = Height;					// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = 8;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			FullScreen = false;
		}
	}

	//AdjustWindowRectEx(&NativeWindow->WindowRect, NativeWindow->dwStyle, FALSE, NativeWindow->dwExStyle);     // Adjust Window To True Requested Size
	UpdateWindowRect();

	switch (Mode)
	{
	// Normal app window
	case WINDOW_DEFAULT:
		NativeWindow->dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;          
		NativeWindow->dwStyle = WS_OVERLAPPEDWINDOW;                    
		break;
	// App window without the title bar
	case WINDOW_DEFAULT_NO_TOPBAR:
		NativeWindow->dwExStyle = NULL;
		NativeWindow->dwStyle = WS_POPUP | WS_BORDER | WS_THICKFRAME; 
		break;
	// Same as default but Width and Height are fullscreen
	case WINDOW_FULLSCREEN_WINDOWED:
		GetPrimaryMonitorSize(&Width, &Height);
		NativeWindow->dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;          
		NativeWindow->dwStyle = WS_OVERLAPPEDWINDOW;
		break;
	case WINDOW_FULLSCREEN_BORDERLESS:
		NativeWindow->dwExStyle = WS_EX_APPWINDOW;        
		NativeWindow->dwStyle = WS_POPUP;                 
		break;
	default:
		return false;
	}

	return true;
}

void VWindow::UpdateWindowRect()
{
	NativeWindow->WindowRect.left = (long)0;              // Set Left Value To 0
	NativeWindow->WindowRect.right = (long)Width;         // Set Right Value To Requested Width
	NativeWindow->WindowRect.top = (long)0;               // Set Top Value To 0
	NativeWindow->WindowRect.bottom = (long)Height;       // Set Bottom Value To Requested Height

	AdjustWindowRectEx(&NativeWindow->WindowRect, NativeWindow->dwStyle, FALSE, NativeWindow->dwExStyle);     // Adjust Window To True Requested Size

}

bool VWindow::CreateNewWindow()
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


	NativeWindow->hInstance = GetModuleHandle(NULL);	// Grab An Instance For Our Window

	NativeWindow->WindowRect.left = (long)0;              // Set Left Value To 0
	NativeWindow->WindowRect.right = (long)Width;         // Set Right Value To Requested Width
	NativeWindow->WindowRect.top = (long)0;               // Set Top Value To 0
	NativeWindow->WindowRect.bottom = (long)Height;       // Set Bottom Value To Requested Height

	// Setup settings to create window
	HandleMode();

	if (!(NativeWindow->hWnd = CreateWindowEx(
		NativeWindow->dwExStyle,      // Extended Style For The Window
		"OpenGL",									// Class Name
		Title.c_str(),								// Window Title
		WS_CLIPSIBLINGS |							// Required Window Style
		WS_CLIPCHILDREN |							// Required Window Style
		NativeWindow->dwStyle,									// Selected Window Style
		X, Y,										// Window Position
		NativeWindow->WindowRect.right - NativeWindow->WindowRect.left,			// Calculate Adjusted Window Width
		NativeWindow->WindowRect.bottom - NativeWindow->WindowRect.top,			// Calculate Adjusted Window Height
		NULL,//parent != nullptr ? parent->NativeWindow->hWnd : NULL,		// No Parent Window
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

	// Share if needed
	if (Parent != nullptr)
	{
		if (wglShareLists(Parent->NativeWindow->hRC, NativeWindow->hRC) == FALSE)
		{
			MessageBox(NULL, "Unable to share GL lists", "WARNING", MB_OK | MB_ICONEXCLAMATION);
		}
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

	CloseFlag = false;

	return true;
}

void VWindow::Close()	// Called when window should be teard down
{
	if (!NativeWindow) return;

	CloseFlag = true;

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

	//if (!UnregisterClass("OpenGL", NativeWindow->hInstance))	// Are We Able To Unregister Class
	//{
	//	MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
	//}

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


bool VWindow::ShouldClose()
{
	return CloseFlag;
}

void VWindow::SignalClose()
{
	PostMessage(NativeWindow->hWnd, WM_CLOSE, NULL, NULL);
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


void VWindow::GetWindowSize(uint32* width, uint32* height)
{
	*width = Width;
	*height = Height;
}

void VWindow::GetPrimaryMonitorSize(uint32* width, uint32* height)
{
	*height = GetSystemMetrics(SM_CYSCREEN);
	*width = GetSystemMetrics(SM_CXSCREEN);
}

bool VWindow::IsOpen()
{
	return (NativeWindow && NativeWindow->hWnd);
}

// -------------------------- Setters -------------------------------
void VWindow::SetPosition(uint32 xPos, uint32 yPos, bool post)
{
	X = xPos;
	Y = yPos;

	if (IsOpen() && post)
	{
		uint32 nw = NativeWindow->WindowRect.right - NativeWindow->WindowRect.left;
		uint32 nh = NativeWindow->WindowRect.bottom - NativeWindow->WindowRect.top;
		MoveWindow(NativeWindow->hWnd,
			X, Y,
			nw, nh,
			TRUE
		);
	}
}

void VWindow::SetSize(uint32 width, uint32 height, bool post)
{
	Width = width;
	Height = height;
	
	if (IsOpen() && post)
	{
		UpdateWindowRect();

		uint32 nw = NativeWindow->WindowRect.right - NativeWindow->WindowRect.left;
		uint32 nh = NativeWindow->WindowRect.bottom - NativeWindow->WindowRect.top;
		MoveWindow(NativeWindow->hWnd,
			X + NativeWindow->WindowRect.left, Y + NativeWindow->WindowRect.top,
			nw, nh,
			TRUE
		);

	}
}

void VWindow::SetTitle(const VString& title, bool post)
{
	Title = title;
	if (IsOpen())
	{
		SetWindowText(NativeWindow->hWnd, TEXT(Title.c_str()));
	}
}

void VWindow::SetMode(EWindowMode mode)
{
	if (Mode != mode)
	{
		Mode = mode;
		if (IsOpen())
		{
			int shwCmd = SW_SHOW;

			switch (Mode)
			{
				// Normal app window
			case WINDOW_DEFAULT:
				NativeWindow->dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
				NativeWindow->dwStyle = WS_OVERLAPPEDWINDOW;
				break;
				// App window without the title bar
			case WINDOW_DEFAULT_NO_TOPBAR:
				NativeWindow->dwExStyle = NULL;
				NativeWindow->dwStyle = WS_POPUP | WS_BORDER | WS_THICKFRAME;
				break;
				// Same as default but Width and Height are fullscreen
			case WINDOW_FULLSCREEN_WINDOWED:
				NativeWindow->dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
				NativeWindow->dwStyle = WS_OVERLAPPEDWINDOW;
				shwCmd = SW_MAXIMIZE;

				break;
			case WINDOW_FULLSCREEN_BORDERLESS:
				NativeWindow->dwExStyle = WS_EX_APPWINDOW;
				NativeWindow->dwStyle = WS_POPUP;

				FullScreen = true;

				DEVMODE dmScreenSettings;								// Device Mode
				memset(&dmScreenSettings, 0, sizeof(dmScreenSettings)); // Makes Sure Memory's Cleared
				dmScreenSettings.dmSize = sizeof(dmScreenSettings);     // Size Of The Devmode Structure
				dmScreenSettings.dmPelsWidth = Width;					// Selected Screen Width
				dmScreenSettings.dmPelsHeight = Height;					// Selected Screen Height
				dmScreenSettings.dmBitsPerPel = 8;					// Selected Bits Per Pixel
				dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

				// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
				if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
				{
					FullScreen = false;
				}

				break;
			}

			UpdateWindowRect();


			SetWindowLong(NativeWindow->hWnd, GWL_STYLE, NativeWindow->dwStyle);
			SetWindowLong(NativeWindow->hWnd, GWL_EXSTYLE, NativeWindow->dwExStyle);

			SetPosition(X, Y, true);
			SetSize(Width, Height, true);

			ShowWindow(NativeWindow->hWnd, shwCmd);                       // Show The Window
			SetForegroundWindow(NativeWindow->hWnd);                      // Slightly Higher Priority
			SetFocus(NativeWindow->hWnd);                             // Sets Keyboard Focus To The Window
		}
	}
}

void VWindow::SetParent(VWindow* parent)
{
	Parent = parent;

	// Cannot reparent window after init
}



void VWindow::SetCloseFlag(bool flag)
{
	CloseFlag = flag;
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

	case WM_SIZE:
	{
		pThis->SetSize(LOWORD(lParam), HIWORD(lParam), false);
		return 0;
	}

	case WM_MOVE:
	{
		uint32 x = LOWORD(lParam);   // horizontal position 
		uint32 y = HIWORD(lParam);   // vertical position 

		pThis->SetPosition(x, y, false);

		return 0;
	}
	case WM_CLOSE:                          // Did We Receive A Close Message?
	{
		pThis->SetCloseFlag(true);
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

	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
