#include "Platform.h"
#include "Vici.h"
#include "Display.h"
#include <stdio.h>

#include <direct.h>
#include "VTime.h"
#include <stdarg.h>


Platform::Platform() : Singleton<Platform>()
{
	_cwd[0] = '\0';
}

Platform::~Platform()
{

}

void Platform::LogString(const char* fmt, ...)
{
	  /* Write the error message */
	va_list args;
  	va_start (args, fmt);
  	vprintf (fmt, args);
  	va_end (args);
}

double Platform::GetTime()
{
	return glfwGetTime();
}

void Platform::EnterLoop(Vici* v)
{
	//for timing
	float last = 0.0f, start = 0.0f, current = 0.0f;

	//the fps
	float fps = 1.0f / _Display->RefreshRate();

	//cache last and start
	start = last = (float)GetTime();

	//get the window
	VRenderContext* rc = _Display->GetRenderContext();
	printf("Rc = %p\n", rc);
	if (rc != NULL)
	{
		printf("Hello again");
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(rc))
		{
			//get the current time
			current = (float)GetTime();

			//loop at target fps
			if (current - last >= fps)
			{
				//update time
				_Time->_time = current - start;
				_Time->_delta_time = (current - last) * _Time->_time_scale;

				//update engine
				if (_Display->HasFocus()) v->Update();

				//render frame
				v->Render();

				/* Swap front and back buffers */
				_Display->SwapBuffers();

				last = (float)GetTime();
			}

			/* Poll for and process events */
			glfwPollEvents();
		}

		glfwTerminate();

	}


	v->OnExit();

}
const char* Platform::Pathify(const char* file)
{
	char* start = (char*)file;
	while(*start != '\0')
	{
		if(*start == '/') *start = '\\';
		start++;
	}
	return file;
}

std::string& Platform::Pathify(std::string& file)
{
	char* start = (char*)(file.c_str());
	while (*start != '\0')
	{
		if (*start == '/') *start = '\\';
		start++;
	}
	return file;

}

std::string& Platform::GetFullPath(std::string& append)
{
	append = _cwd + append;
	return Pathify(append);
}
void Platform::SetCwd(const char* executable_path, bool trim_end)
{
	if(trim_end)
	{
		size_t back = strlen(executable_path);
		char* end = (char*)&executable_path[back];

		//loop backwards
		while(*--end != '\\')
			;

		//set zero-terminator
		*end = '\0';
	}

	//set cwd
	strcpy(_cwd, executable_path);
}