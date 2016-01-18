#include "Display.h"
#include "Vici.h"
#include <string>


Display::Display() : Singleton<Display>()
{
	ScreenWidth = ScreenHeight = ContextWidth = ContextHeight = 0;
	RefreshRate = 60;
	RenderContext = NULL;
	bHasFocus = true;
	bFullscreen = false;
}

Display::~Display()
{

}

//called when focus to window has changed (minimized / opened)
void OnFocusChanged(VWindow* window, int focus)
{
	//focus = `GL_TRUE` if the window was iconified, or `GL_FALSE` if it was restored.
	if (focus != GL_TRUE)
	{
		_Display->SetHasFocus(false);
		_Vici->OnEnteredBackground();
	}
	else
	{
		_Display->SetHasFocus(true);
		_Vici->OnEnteredFocus();
	}
		
}

void Display::SetRenderContext(VRenderContext* context)
{
	RenderContext = context;
	
	glfwGetWindowSize(RenderContext, &ContextWidth, &ContextHeight);
	
	/* Make the window's context current */
	glfwMakeContextCurrent(RenderContext);
	
	ClearRenderArea();
}

void Display::Init()
{
	/* Initialize the library */
	if (!glfwInit())
	{
		_Platform->LogString("Cannot init glfw\n");
		return;
	}

	/* If fullscreen we need to set the width and height to the monitor width and height */
	if (bFullscreen)
	{
		//get the monitor info
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		//get hints
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		//set w and h
		ContextWidth = mode->width;
		ContextHeight = mode->height;
	}

	/* Create a windowed mode window and its OpenGL context */
	RenderContext = glfwCreateWindow(ContextWidth, ContextHeight, Title.c_str(), bFullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	if (RenderContext == NULL)
	{
		glfwTerminate();
		_Platform->LogString("Could not load window\n");
		return;
	}
	
	SetRenderContext(RenderContext);

	/* Set callbacks */
	glfwSetWindowSizeCallback(RenderContext, Display::OnResize);

	glfwSetWindowFocusCallback(RenderContext, OnFocusChanged);

#ifdef VICI_WINDOWS
	//init glew
	if (glewInit() != GLEW_OK)
		_Platform->LogString("Could not init glew library\n");
#endif
	//get the monitor info
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	//set refresh rate
	RefreshRate = mode->refreshRate;
	ScreenWidth = mode->width;
	ScreenHeight = mode->height;
}

void Display::SetSize(int w, int h, bool force_window_resize)
{
	ContextWidth = w;
	ContextHeight = h;

	if (force_window_resize)
	{
		glfwSetWindowSize(RenderContext, w, h);
	}
}

void Display::OnResize(VWindow* win, int w, int h)
{
	_Display->ContextWidth = w;
	_Display->ContextHeight = h;
}

void Display::ClearRenderArea()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Display::SwapBuffers()
{
	glfwSwapBuffers(RenderContext);
}