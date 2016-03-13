#include "stdio.h"
#include "Input.h"
#include "Window.h"
#include "Time.h"

#include "MathLib.h"

void Tests()
{
	Matrix4f m3 = Matrix4f::Identity();
	m3(0, 0) = 10;
	m3(0, 1) = 15;
	m3(0, 2) = 23;

	m3(1, 0) = 12;
	m3(1, 1) = 21;
	m3(1, 2) = 22;

	m3(2, 0) = 4;
	m3(2, 1) = 7;
	m3(2, 2) = 3;

	float det = m3.Determinant();

	printf("Hello");
}



// Called when key is pressed
void KeyCallbackFn(VWindow* win, VButton* button)
{
	printf("Key %d action = %d\n", button->Key, button->Action);
	if (button->Key == V_KEY_ESCAPE &&  button->Action == V_KEY_PRESS)
	{
		win->SignalShouldClose();
	}
}

void MouseButtonCallbackFn(VWindow* win, VMouseButton* button)
{
	printf("Mouse button: %d action = %d\n", button->Button, button->Action);
}

void CursorPosCallbackFn(VWindow* win, VMouseInfo* mi)
{
	printf("Cursor pos X=%.2f, Y=%.2f\n", mi->X, mi->Y);
}

void CursorEnteredCallbackFn(VWindow* win, bool entered)
{
	printf(entered ? "Mouse entered\n" : "Mouse left\n");
}

void ScrollCallback(VWindow* win, VScrollInfo* si)
{
	printf("Scroll X = %.2f Y = %.2f\n", si->XOffset, si->YOffset);
}

void FileDropped(VWindow* win, VFileDropInfo* fdi)
{
	for (int i = 0; i < fdi->Count; i++)
		printf("File %s \n", fdi->Paths[i]);
}

int main(int argc, char** argv)
{
	VWindow win(500, 500);

	// Set callbacks
	win.SetKeyCallbackFn(KeyCallbackFn);
	win.SetMouseButtonCallbackFn(MouseButtonCallbackFn);
	win.SetCursorPosCallbackFn(CursorPosCallbackFn);
	win.SetCursorEnteredCallbackFn(CursorEnteredCallbackFn);
	win.SetScrollCallbackFn(ScrollCallback);
	win.SetFileDropCallbackFn(FileDropped);

	win.MakeCurrent();

	Tests();


	float t = 0.0f;
	float dt = 0.01f;

	VTime::GetInstance()->SetFixedDeltaTime(dt);		// Fixed delta time will not change

	// Initialize
	VTime::GetInstance()->UpdateTime();		// Update time for this


	float currentTime = VTime::GetInstance()->GetTime();
	float accumulator = 0.0f;

	while (!win.ShouldClose())
	{
		VTime::GetInstance()->UpdateTime();		// Update time for this

		float newTime =	VTime::GetInstance()->GetTime();
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