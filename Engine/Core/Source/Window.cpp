#include "Window.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "Input.h"

// Static init
bool VWindow::GLFWInit = false;

// Helpful macros
#define AS_NATIVEWIN(ptr) ((GLFWwindow*)ptr)

VWindow::VWindow(int w, int h, const char* title, bool fullscreen)
	:Width(w),
	Height(h),
	NativeWindow(nullptr),
	KeyCallback(nullptr),
	MouseButtonCallback(nullptr),
	CursorEnterCallback(nullptr),
	CursorPosCallback(nullptr),
	ScrollCallback(nullptr),
	FileDropCallback(nullptr)
{
	// Only do if glfw is init
	if (!GLFWInit && glfwInit())
	{
		glfwSetErrorCallback(VWindow::ErrorCallback);
		GLFWInit = true;
	}
	
	NativeWindow = glfwCreateWindow(w, h, title, fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
	if (!NativeWindow)
	{
		printf("Failed to create window\n");
		return;
	}

	// Make sure we keep a reference to this
	glfwSetWindowUserPointer(AS_NATIVEWIN(NativeWindow), this);

	// Set current so we can set VSync
	MakeCurrent();
	glfwSwapInterval(1);
}

VWindow::~VWindow()
{
	Close();	// Ensure window is closed
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

void VWindow::GetFrameBufferSize(int* width, int* height)
{
	glfwGetFramebufferSize(AS_NATIVEWIN(NativeWindow), width, height);
}

void VWindow::GetPrimaryMonitorSize(int* width, int* height)
{
	// Ensure init
	if (!GLFWInit && glfwInit())
	{
		glfwSetErrorCallback(VWindow::ErrorCallback);
		GLFWInit = true;
	}

	const GLFWvidmode* data = glfwGetVideoMode(glfwGetPrimaryMonitor());
	*width = data->width;
	*height = data->height;
}