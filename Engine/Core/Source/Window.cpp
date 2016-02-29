#include "Window.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

// Static init
bool VWindow::GLFWInit = false;

// Helpful macros
#define AS_NATIVEWIN(ptr) ((GLFWwindow*)ptr)

VWindow::VWindow(int w, int h, const char* title)
	:Width(w),
	Height(h),
	NativeWindow(nullptr),
	KeyCallback(nullptr)
{
	// Only do if glfw is init
	if (!GLFWInit && glfwInit())
	{
		glfwSetErrorCallback(VWindow::ErrorCallback);
		GLFWInit = true;
	}

	NativeWindow = glfwCreateWindow(w, h, title, nullptr, nullptr);
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
		vWindow->KeyCallback(vWindow, key, scancode, action, mods);
}	
// --- End of internal callbacks

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
	if(NativeWindow != nullptr)
		glfwDestroyWindow(AS_NATIVEWIN(NativeWindow));
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

void VWindow::GetFrameBufferSize(int* width, int* height)
{
	glfwGetFramebufferSize(AS_NATIVEWIN(NativeWindow), width, height);
}