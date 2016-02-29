#include "stdio.h"
#include "Window.h"
#include "Time.h"

// Called when key is pressed
void KeyCallbackFn(VWindow* win, int key, int scancode, int action, int mods)
{
	printf("Key %d action = %d\n", key, action);
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

	float t = 0.0f;
	float dt = 0.01f;

	float currentTime = VTime::GetTime();
	float accumulator = 0.0f;

	while (!win.ShouldClose())
	{
		float newTime = VTime::GetTime();
		float frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
			frameTime = 0.25f;

		currentTime = newTime;
		accumulator += frameTime;

		// UPDATING --
		while (accumulator >= dt)
		{
			// TODO:: Fixed update code goes here


			t += dt;
			accumulator -= dt;
		}

		// TODO:: Single frame update code here


		// TODO:: Render here


		// Swap buffers
		win.Swapbuffers();

		// Poll events
		win.PollEvents();
	}

	
	return 0;
}