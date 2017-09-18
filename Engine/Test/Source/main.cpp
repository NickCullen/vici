#include "Window.h"
#include <stdio.h>

int main(int argc, char** argv)
{
	Platform::VWindow w;

	w.Open(10, 10, 100, 200);
	
	while(w.IsOpen())
	{
		w.PollEvents();
	}

	return 0;
}



