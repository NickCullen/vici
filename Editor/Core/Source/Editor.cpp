#include "Editor.h"
#include "GameView.h"
#include "SceneView.h"
#include "Time.h"
#include "Window.h"

VEditor::VEditor()
	:SceneView(nullptr),
	GameView(nullptr),
	Quit(false)
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

int VEditor::Run()
{
	float t = 0.0f;
	float dt = 0.01f;

	float currentTime = VTime::GetTime();
	float accumulator = 0.0f;

	VPanel* panels[] = { GameView, SceneView };
	int panelCount = 2;

	while (!Quit)
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

		// Render panels
		for (int i = 0; i < panelCount; i++)
		{
			panels[i]->Render();

			panels[i]->PostRender();

		}

		// Poll events
		for (int i = 0; i < panelCount; i++)
			panels[i]->PollEvents();
	}

	return 0;
}