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

//GLEWContext* glewGetContext()
//{
//	return (GLEWContext*)VWindow::CurrentContext->glewContext;
//}
#endif

// Definitions of glewGetContext
VWindow::VWindow(int w, int h, const char* title, EWindowMode mode, VWindow* parent)
	:UserData(nullptr),
	NativeWindow(nullptr),
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

	const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	switch (mode)
	{
		// Simply open the window with specified width and height
	case WINDOW_DEFAULT:
		NativeWindow = glfwCreateWindow(w, h, title, nullptr, parent ? AS_NATIVEWIN(parent->NativeWindow) : nullptr); 
		break;

		// Open window using the video mode to get the window features fullscreen
	case WINDOW_FULLSCREEN_WINDOWED:
		glfwWindowHint(GLFW_RED_BITS, vidMode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, vidMode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, vidMode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, vidMode->refreshRate);
		glfwWindowHint(GLFW_DECORATED, GL_TRUE);
		NativeWindow = glfwCreateWindow(vidMode->width, vidMode->height-30, title, nullptr, NULL);
		break;

		// No window border
	case WINDOW_FULLSCREEN_BORDERLESS:
		NativeWindow = glfwCreateWindow(w, h, title, glfwGetPrimaryMonitor(), parent ? AS_NATIVEWIN(parent->NativeWindow) : nullptr);
		break;

		// Assume default window
	default:
		NativeWindow = glfwCreateWindow(w, h, title, nullptr, parent ? AS_NATIVEWIN(parent->NativeWindow) : nullptr);
		break;
	}
	
	if (!NativeWindow)
	{
		printf("Failed to create window\n");
		return;
	}

	// Reset hints
	glfwDefaultWindowHints();

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

	glfwSwapInterval(1);

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
		GLFWInit = true;
	}
	return true;
}


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