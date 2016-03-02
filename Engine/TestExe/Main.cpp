#include "stdio.h"
#include "Input.h"
#include "Window.h"
#include "Time.h"
#include "VertexBuffer.h"

struct VEC2
{
	float x;
	float y;
};

struct VEC3
{
	float x;
	float y;
	float z;
};

void Tests()
{
	// Create buffer object
	VVertexBuffer* vb = new VVertexBuffer();

	// Tell the buffer object how many elements per vertex
	int vec2ID = vb->AddElement<VEC2>();
	int vec3ID = vb->AddElement<VEC3>();

	// Allocate some space
	vb->AllocateVertices(1);

	int x = 1;
	int y = 2;
	int i = 1;
	if (vb->Lock())
	{
		for (int j = 0; j < 5; j++)
		{
			vb->AddVertex();	// Allocate for this vertex

			VEC2 v2;
			v2.x = x++ * i;
			v2.y = y++ * i * i;

			VEC3 v3;
			v3.x = v2.x * 0.25;
			v3.y = v2.y * 0.75;
			v3.z = i;

			vb->AddData<VEC2>(v2, vec2ID);
			vb->AddData<VEC3>(v3, vec3ID);

		}
		i++;
	}

	delete(vb);
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