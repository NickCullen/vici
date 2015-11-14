#include <stdio.h>
#include "Vici.h"
#include "Platform.h"
#include "ViciProject.h"
#include "Display.h"

int main(int argc, char** argv)
{
	Vici* v = new Vici();
	ViciProject* proj = new ViciProject();
	
	// Default values
	char* runningDirectory = argv[0];
	
	// Parse args
	if (argc > 1)
	{
		for(int i = 1; i < argc; i+=2)
		{
			char* param = argv[i];
			char* value = argv[i+1];
			
			// Running Directory param
			if(strcmp(param, "-rd") == 0)
			{
				runningDirectory = value;
			}
		}
	}
	
	// Set current working directory
	_Platform->SetCwd(runningDirectory, true);
	
	// Setup Display
	
	// For quickly debugging window
	if (!glfwInit())
	{
		_Platform->LogString("Cannot init glfw\n");
		return -1;
	}
	
	// Initialise for quick running	
	Display* display = new Display();
	VWindow* win = glfwCreateWindow(800, 600, "Test", NULL, NULL);
	printf("Window = %p\n", win);
	
	display->SetRenderContext(win);
	
	v->Init();

	v->Begin();

	_Platform->EnterLoop(v);

	delete(display);
	delete(proj);
	delete(v);
	
	return 0;
}

