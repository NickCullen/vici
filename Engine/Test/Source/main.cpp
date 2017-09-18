#include "Window.h"
#include <stdio.h>

using namespace Platform;


int main(int argc, char** argv)
{
	VWindow w;

	if (!w.Open(10, 10, 800, 700))
		return -1;


	while (true)
	{
		w.PollEvents();

	}
	return 0;
}


