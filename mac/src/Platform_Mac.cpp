#include "Platform.h"
#include "GLFW/glfw3.h"
#include <stdio.h>
#include "OpenGLRenderer.h"
#include "Vici.h"
#include <unistd.h>

GLFWwindow* window = NULL;

char* Platform_Getcwd(char* buff, int len)
{
    //hard coded for now
    strcpy(buff,"/Users/Nick/Documents/vici/build");
    //getcwd(buff,len);
    return buff;
}

double Platform_GetTime()
{
	return glfwGetTime();
}


bool Platform_OpenWindow(int w, int h, const char* title)
{
	/* Initialize the library */
	if (!glfwInit())
		return false;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(w, h, title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	return true;
}

void Platform_EnterLoop(Vici* v)
{
	if (window != NULL)
	{
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			v->Update();

			v->Render();

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

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