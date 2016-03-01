#include "Editor.h"
#include "GameView.h"
#include "SceneView.h"
#include "Time.h"
#include "Window.h"

VEditor::VEditor()
	:SceneView(nullptr),
	GameView(nullptr),
	IsPlaying(false)
{

}

VEditor::~VEditor()
{
	if (GameView)
		delete(GameView);
	if (SceneView)
		delete(SceneView);
}

bool VEditor::Init(int argc, int argv)
{
	GameView = new VGameView();
	if (!GameView || !GameView->Init())
	{
		return false;
	}

	SceneView = new VSceneView();
	if (!SceneView || !SceneView->Init())
	{
		return false;
	}

	return true;
}

// Will need to put this on a thread at some point
void VEditor::GameLoop()
{
	float t = 0.0f;
	float dt = 0.01f;

	float currentTime = VTime::GetTime();
	float accumulator = 0.0f;

	while (!GameView->Window->ShouldClose())
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
		GameView->Window->Swapbuffers();

		// Poll events
		GameView->Window->PollEvents();
	}
}
int VEditor::Run()
{
	GameLoop();
	return 0;
}