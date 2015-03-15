#include "Platform.h"
#include "GLFW/glfw3.h"
#include <stdio.h>
#include "OpenGLRenderer.h"
#include "Vici.h"
#include <unistd.h>
#include <stdarg.h>

GLFWwindow* window = NULL;

void Platform_LogString(const char* fmt, ...)
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

