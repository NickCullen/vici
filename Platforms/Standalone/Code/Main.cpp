#include <stdio.h>
#include "Core/EngineIncludes.h"
#include "PIL/Platform/Window.h"

// Main
int main(int argc, char** argv)
{
	// Setup running directory path
	const char* path = argv[0];
	VFilePath runningDirectory = VFilePath::TrimPath((char*)path);

	VEnvironment::GetInstance()->Put(ItemToString(FILE_RUNNING_DIRECTORY), runningDirectory);

	// TODO:: This window creation will load from a file...
	VWindow win;
	win.SetSize(512, 512);
	win.SetTitle("My Window");
	if (!win.CreateNewWindow())
	{
		printf("Error creating window\n");
		return 1;
	}
	win.MakeContextCurrent();


	// Setup stuff
	VEngine* vici = new VEngine();
	vici->Init(0, nullptr);

	float t = 0.0f;
	float dt = 0.01f;

	// Start time class
	VTime::GetInstance()->SetFixedDeltaTime(dt);
	VTime::GetInstance()->UpdateTime();

	float currentTime = (float)VTime::GetInstance()->GetTime();
	float accumulator = 0.0f;

	while (!Quit)
	{
		VTime::GetInstance()->UpdateTime();	// Update time

		float newTime = (float)VTime::GetInstance()->GetTime();
		float frameTime = newTime - currentTime;

		VTime::GetInstance()->SetDeltaTime(frameTime);		// Set per frame delta time

		if (frameTime > 0.25f)
			frameTime = 0.25f;

		currentTime = newTime;
		accumulator += frameTime;


		// UPDATING --
		while (accumulator >= dt)
		{
			// TODO:: Fixed update code goes here
			if (IsPlaying)
			{
				vici->FixedUpdate();
			}

			t += dt;
			accumulator -= dt;
		}

		// TODO:: Single frame update code here
		if (IsPlaying)
		{
			vici->Update();
		}

		// TODO:: Render here
		vici->Render();

		// Swap buffers
		win.SwapBuffers();

		// Poll events
		win.PollEvents();

	}

	return 0;
}