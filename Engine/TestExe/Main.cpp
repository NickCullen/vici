#include "stdio.h"
#include "Window.h"
#include "Time.h"
#include "VString.h"

void Tests()
{
	VString str = "Hello world";

	printf(str);
}
// Called when key is pressed
void KeyCallbackFn(VWindow* win, int key, int scancode, int action, int mods)
{
	printf("Key %d action = %d\n", key, action);
	if (key == V_KEY_ESCAPE && action == V_KEY_PRESS)
	{
		win->SignalShouldClose();
	}
}

void MouseButtonCallbackFn(VWindow* win, int button, int action, int mods)
{
	printf("Mouse button: %d action = %d\n", button, action);
}

void CursorPosCallbackFn(VWindow* win, double xpos, double ypos)
{
	printf("Cursor pos X=%.2f, Y=%.2f\n", xpos, ypos);
}

int main(int argc, char** argv)
{
	Tests();

	VWindow win(500, 500);

	// Set callbacks
	win.SetKeyCallbackFn(KeyCallbackFn);
	win.SetMouseButtonCallbackFn(MouseButtonCallbackFn);
	win.SetCursorPosCallbackFn(CursorPosCallbackFn);

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