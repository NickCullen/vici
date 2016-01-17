#include "Display.h"
#include "Vici.h"
#include "Xml.h"
#include <string>


Display::Display() : Singleton<Display>()
{
	_screen_width = _screen_height = _context_width = _context_height = 0;
	_refresh_rate = 60;
	_render_context = NULL;
	_has_focus = true;
	_fullscreen = false;
}

Display::~Display()
{

}

void Display::Serialize(ArchiveOut& archive)
{
	_SERIALIZE_VAR(_title, archive);
    _SERIALIZE_VAR(_context_width, archive);
    _SERIALIZE_VAR(_context_height, archive);
    _SERIALIZE_VAR(_fullscreen, archive);
}
void Display::Deserialize(ArchiveIn& archive)
{
	archive(_title, _context_width, _context_height, _fullscreen);
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
	_render_context = context;
	
	glfwGetWindowSize(_render_context, &_context_width, &_context_height);
	
	/* Make the window's context current */
	glfwMakeContextCurrent(_render_context);
	
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
	if (_fullscreen)
	{
		//get the monitor info
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		//get hints
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		//set w and h
		_context_width = mode->width;
		_context_height = mode->height;
	}

	/* Create a windowed mode window and its OpenGL context */
	_render_context = glfwCreateWindow(_context_width, _context_height, _title.c_str(), _fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	if (_render_context == NULL)
	{
		glfwTerminate();
		_Platform->LogString("Could not load window\n");
		return;
	}
	
	SetRenderContext(_render_context);

	/* Set callbacks */
	glfwSetWindowSizeCallback(_render_context, Display::OnResize);

	glfwSetWindowFocusCallback(_render_context, OnFocusChanged);

#ifdef VICI_WINDOWS
	//init glew
	if (glewInit() != GLEW_OK)
		_Platform->LogString("Could not init glew library\n");
#endif
	//get the monitor info
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	//set refresh rate
	_refresh_rate = mode->refreshRate;
	_screen_width = mode->width;
	_screen_height = mode->height;
}

void Display::SetSize(int w, int h, bool force_window_resize)
{
	_context_width = w;
	_context_height = h;

	if (force_window_resize)
	{
		glfwSetWindowSize(_render_context, w, h);
	}
}

void Display::OnResize(VWindow* win, int w, int h)
{
	_Display->_context_width = w;
	_Display->_context_height = h;
}

void Display::ClearRenderArea()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Display::SwapBuffers()
{
	glfwSwapBuffers(_render_context);
}