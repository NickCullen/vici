#include "stdio.h"
#include "Window.h"

// Called when key is pressed
void KeyCallbackFn(VWindow* win, int key, int scancode, int action, int mods)
{
	if (key == V_KEY_ESCAPE && action == V_KEY_PRESS)
	{
		win->SignalShouldClose();
	}
}

int main(int argc, char** argv)
{
	VWindow win(500, 500);

	// Set callbacks
	win.SetKeyCallbackFn(KeyCallbackFn);

	win.MakeCurrent();

	while (!win.ShouldClose())
	{
		// Render here

		// Swap buffers
		win.Swapbuffers();

		// Poll events
		win.PollEvents();
	}

	
	return 0;
}