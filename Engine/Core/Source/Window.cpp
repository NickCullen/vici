#include "Window.h"
#include "Glew.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "Input.h"
#include "Renderer.h"

// Static init
bool VWindow::GLFWInit = false;
int VWindow::Count = 0;

// Helpful macros
#define AS_NATIVEWIN(ptr) ((GLFWwindow*)ptr)

#ifdef GLEW_MX	// Context switching stuff
VWindow* VWindow::CurrentContext = nullptr;

GLEWContext* glewGetContext()
{
	return (GLEWContext*)VWindow::CurrentContext->glewContext;
}
#endif

// Definitions of glewGetContext
VWindow::VWindow(int w, int h, const char* title, bool fullscreen, VWindow* parent)
	:UserData(nullptr),
	NativeWindow(nullptr),
	KeyCallback(nullptr),
	MouseButtonCallback(nullptr),
	CursorEnterCallback(nullptr),
	CursorPosCallback(nullptr),
	ScrollCallback(nullptr),
	FileDropCallback(nullptr),
	WindowID(++Count)
{
#ifdef GLEW_MX
	this->glewContext = nullptr;
	VWindow* PreviousContext = CurrentContext;
#endif
	

	// ensure init
	if (!Init())
	{
		printf("Cannot initialize window library\n");
		return;
	}

	NativeWindow = glfwCreateWindow(w, h, title, fullscreen ? glfwGetPrimaryMonitor() : nullptr, parent ? AS_NATIVEWIN(parent->NativeWindow) : nullptr);
	if (!NativeWindow)
	{
		printf("Failed to create window\n");
		return;
	}

	// Reset hints
	//glfwDefaultWindowHints();

	// Make sure we keep a reference to this
	glfwSetWindowUserPointer(AS_NATIVEWIN(NativeWindow), this);

	
#ifdef GLEW_MX
	// Create glew context
	this->glewContext = (void*)new GLEWContext();
#endif

	// Set current so we can init glew for this context
	MakeCurrent();
	
	// Make sure glew is initialized for this context
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("Failed to init glew\n");
	}

	//glfwSwapInterval(1);

	MakeCurrent(PreviousContext);
}

VWindow::~VWindow()
{
	Close();	// Ensure window is closed
}

bool VWindow::Init()
{
	// Only do if glfw is init
	if (!GLFWInit && glfwInit())
	{
		glfwSetErrorCallback(VWindow::ErrorCallback);

		GLFWInit = true;
	}
	return true;
}

// INTERNAL CALLBACKS ---
void VWindow::ErrorCallback(int error, const char* desc)
{
	printf("Error: %d\n", error);
	printf("Decription: %s\n", desc);
}

void VWindow::KeyCallbackFn(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	VWindow* vWindow = (VWindow*)glfwGetWindowUserPointer(win);
	if (vWindow != nullptr && vWindow->KeyCallback != nullptr)
	{
		VButton btn(key, scancode, action, mods);
		vWindow->KeyCallback(vWindow, &btn);
	}
}	

void VWindow::MouseButtonCallbackFn(GLFWwindow* win, int button, int action, int mods)
{
	VWindow* vWindow = (VWindow*)glfwGetWindowUserPointer(win);
	if (vWindow != nullptr && vWindow->MouseButtonCallback != nullptr)
	{
		VMouseButton mb(button, action, mods);
		vWindow->MouseButtonCallback(vWindow, &mb);
	}
}

void VWindow::CursorPositionCallbackFn(GLFWwindow* win, double xpos, double ypos)
{
	VWindow* vWindow = (VWindow*)glfwGetWindowUserPointer(win);
	if (vWindow != nullptr && vWindow->CursorPosCallback != nullptr)
	{
		VMouseInfo mi((float)xpos, (float)ypos);
		vWindow->CursorPosCallback(vWindow, &mi);
	}
}

void VWindow::CursorEnteredCallbackFn(GLFWwindow* win, int entered)
{
	VWindow* vWindow = (VWindow*)glfwGetWindowUserPointer(win);
	if (vWindow != nullptr && vWindow->CursorEnterCallback != nullptr)
		vWindow->CursorEnterCallback(vWindow, entered == GL_TRUE);
}

void VWindow::ScrollCallbackFn(GLFWwindow* win, double x, double y)
{
	VWindow* vWindow = (VWindow*)glfwGetWindowUserPointer(win);
	if (vWindow != nullptr && vWindow->ScrollCallback != nullptr)
	{
		VScrollInfo si((float)x, (float)y);
		vWindow->ScrollCallback(vWindow, &si);
	}
}

void VWindow::FileDropCallbackFn(GLFWwindow* win, int count, const char** files)
{
	VWindow* vWindow = (VWindow*)glfwGetWindowUserPointer(win);
	if (vWindow != nullptr && vWindow->FileDropCallback != nullptr)
	{
		VFileDropInfo fd(count, files);
		vWindow->FileDropCallback(vWindow, &fd);
	}
}
// --- End of internal callbacks

void VWindow::SetPosition(int xPos, int yPos)
{
	glfwSetWindowPos(AS_NATIVEWIN(NativeWindow), xPos, yPos);
}
void VWindow::MakeCurrent()
{
	glfwMakeContextCurrent(AS_NATIVEWIN(NativeWindow));
	// Window ID starts at 1 so we need to negate it for 0 arrays
	VRenderer::GetInstance()->SetContextID(WindowID - 1);
#ifdef GLEW_MX
	CurrentContext = this;
#endif
}

void VWindow::MakeCurrent(VWindow* ctx)
{
	if (ctx != nullptr)
	{
		glfwMakeContextCurrent(AS_NATIVEWIN(ctx->NativeWindow));
		// Window ID starts at 1 so we need to negate it for 0 arrays
		VRenderer::GetInstance()->SetContextID(ctx->WindowID - 1);
#ifdef GLEW_MX
		CurrentContext = ctx;
#endif
	}
}

bool VWindow::ShouldClose()
{
	return (glfwWindowShouldClose(AS_NATIVEWIN(NativeWindow)) > 0);
}

void VWindow::SignalShouldClose()
{
	glfwSetWindowShouldClose(AS_NATIVEWIN(NativeWindow), GL_TRUE);
}

void VWindow::Swapbuffers()
{
	glfwSwapBuffers(AS_NATIVEWIN(NativeWindow));
}

void VWindow::PollEvents()
{
	glfwPollEvents();
}

void VWindow::Close()
{
	if (NativeWindow != nullptr)
	{
		glfwDestroyWindow(AS_NATIVEWIN(NativeWindow));
		NativeWindow = nullptr;
	}
}

void VWindow::TerminateAll()
{
	if (GLFWInit)
	{
		glfwTerminate();
		GLFWInit = false;
	}
}

void VWindow::SetKeyCallbackFn(Vkeyfun keyFn)
{
	glfwSetKeyCallback(AS_NATIVEWIN(NativeWindow), VWindow::KeyCallbackFn);	// Set internal
	KeyCallback = keyFn;	// Store pointer
}

void VWindow::SetMouseButtonCallbackFn(Vmousebuttonfun mouseFn)
{
	glfwSetMouseButtonCallback(AS_NATIVEWIN(NativeWindow), VWindow::MouseButtonCallbackFn);
	MouseButtonCallback = mouseFn;
}

void VWindow::SetCursorPosCallbackFn(Vcursorposfun cursorFn)
{
	glfwSetCursorPosCallback(AS_NATIVEWIN(NativeWindow), VWindow::CursorPositionCallbackFn);
	CursorPosCallback = cursorFn;
}

void VWindow::SetCursorEnteredCallbackFn(Vcursorenterfun cursorFn)
{
	glfwSetCursorEnterCallback(AS_NATIVEWIN(NativeWindow), VWindow::CursorEnteredCallbackFn);
	CursorEnterCallback = cursorFn;
}

void VWindow::SetScrollCallbackFn(Vscrollfun scrollFn)
{
	glfwSetScrollCallback(AS_NATIVEWIN(NativeWindow), VWindow::ScrollCallbackFn);
	ScrollCallback = scrollFn;
}

void VWindow::SetFileDropCallbackFn(Vdropfun dropFn)
{
	glfwSetDropCallback(AS_NATIVEWIN(NativeWindow), VWindow::FileDropCallbackFn);
	FileDropCallback = dropFn;
}

void VWindow::GetWindowSize(int* width, int* height)
{
	glfwGetWindowSize(AS_NATIVEWIN(NativeWindow), width, height);
}

void VWindow::GetFrameBufferSize(int* width, int* height)
{
	glfwGetFramebufferSize(AS_NATIVEWIN(NativeWindow), width, height);
}

void VWindow::GetPrimaryMonitorSize(int* width, int* height)
{
	// ensure init
	if (!Init())
	{
		printf("Cannot initialize window library\n");
		return;
	}

	const GLFWvidmode* data = glfwGetVideoMode(glfwGetPrimaryMonitor());
	*width = data->width;
	*height = data->height;
}

void VWindow::SetBorderHint(bool show)
{
	glfwWindowHint(GLFW_DECORATED, show ? GL_TRUE : GL_FALSE);
}