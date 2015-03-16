#include "Platform.h"
#include <windows.h>
#include "glew.h"
#include <stdio.h>
#include "OpenGLRenderer.h"
#include "Vici.h"
#include <direct.h>
#include "VTime.h"
#include <stdarg.h>

void Platform_LogString(const char* fmt, ...)
{
	/* Write the error message */
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
}

char* Platform_Getcwd(char* buff, int len)
{
	return _getcwd(buff, len);
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
	float fps = 1.0f / _Display->RefreshRate();

	//cache last and start
	start = last = (float)Platform_GetTime();

	//get the window
	VWindow* win = _Display->Window();

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
				_Time->SetTime(current - start);
				_Time->SetDeltaTime((current - last) * _Time->TimeScale());

				//update engine
				if (_Display->HasFocus()) v->Update();

				v->Render();

				/* Swap front and back buffers */
				glfwSwapBuffers(win);
		
				last = (float)Platform_GetTime();
			}
			
			/* Poll for and process events */
			glfwPollEvents();
		}

		glfwTerminate();

	}


	_Vici->OnExit();

}

const char* Platform_Pathify(const char* file)
{
	char* start = (char*)file;
	while(*start != '\0')
	{
		if(*start == '/') *start = '\\';
		start++;
	}
	return file;
}
