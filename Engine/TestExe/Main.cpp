#include "stdio.h"
#include "Input.h"
#include "Window.h"
#include "Time.h"
#include "VertexBuffer.h"
#include "Dictionary.h"


struct VEC2
{
	float x;
	float y;

	VEC2(float _x, float _y)
		:x(_x),
		y(_y)
	{}

};

struct VEC3
{
	float x;
	float y;
	float z;
};

#include <random>
#include <time.h>

void Tests()
{
	srand(3250239752);
	VDictionary<int>* dict = new VDictionary<int>();

	// Stress test
	const int max = 40000;
	const int strSize = 5;
	char buff[strSize];
	for (int i = 0; i < max; i++)
	{
		for (int j = 0; j < strSize; j++)
			buff[j] = 65 + rand() % 25;

		dict->Insert(buff, i);
	}
	dict->Insert("MyInt1", 64);

	bool exists = dict->KeyExists("MyInt1");
	int out = 0;
	if (dict->Get("MyInt1", &out))
	{
		printf("Retrieved = %d\n", out);
	}


	delete(dict);
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