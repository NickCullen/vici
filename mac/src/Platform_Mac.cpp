#include "Platform.h"
#include "GLFW/glfw3.h"
#include <stdio.h>
#include "OpenGLRenderer.h"
#include "Vici.h"
#include <unistd.h>
#include <stdarg.h>

GLFWwindow* window = NULL;

void Platform_LogString(char* fmt, ...)
{
	  /* Write the error message */
	va_list args;
  	va_start (args, fmt);
  	vprintf (fmt, args);
  	va_end (args);

}

char* Platform_Getcwd(char* buff, int len)
{
    //hard coded for now
    //strcpy(buff,"/Users/Nick/Documents/vici/build");
    getcwd(buff,len);
    return buff;
}

double Platform_GetTime()
{
	return glfwGetTime();
}

VWindow* Platform_OpenWindow(int* w, int* h, const char* title, bool fullscreen)
{
	/* Initialize the library */
	if (!glfwInit())
		return false;

	/* If fullscreen we need to set the width and height to the monitor width and height */
	if (fullscreen)
	{
		//get the monitor info
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		//get hints
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		//set w and h
		*w = mode->width;
		*h = mode->height;
	}

	/* Create a windowed mode window and its OpenGL context */
	VWindow* window = glfwCreateWindow(*w, *h, title, fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Set callbacks */
	glfwSetWindowSizeCallback(window, Display::OnResize);

	return window;
}

void Platform_EnterLoop(Vici* v)
{
	//for timing
	float last = 0.0f, start = 0.0f, current = 0.0f;

	//the fps
	float fps = 1.0f / Display::RefreshRate();

	//cache last and start
	start = last = (float)Platform_GetTime();

	//get the window
	VWindow* win = Display::Window();

	if (win != NULL)
	{
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(win))
		{
			//get the current time
			current = (float)Platform_GetTime();

			//loop at target fps
			if (current - last >= fps)
			{
				//update time
				VTime::_time = current - start;
				VTime::_delta_time = (current - last) * VTime::_time_scale;

				//update engine
				v->Update();

				//render frame
				v->Render();

				/* Swap front and back buffers */
				glfwSwapBuffers(win);

				last = (float)Platform_GetTime();
			}
			
			/* Poll for and process events */
			glfwPollEvents();
		}

		glfwTerminate();
		return;
	}
}

const char* Platform_Pathify(const char* file)
{
	char* start = (char*)file;
	while(*start != '\0')
	{
		if(*start == '\\') *start = '/';
		start++;
	}
	return file;
}

