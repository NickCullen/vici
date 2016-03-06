#include "Editor.h"
#include "GameView.h"
#include "SceneView.h"
#include "Time.h"
#include "Window.h"
#include "Engine.h"
#include "MainWindow.h"
#include "Renderer.h"

VEditor::VEditor()
	:SceneView(nullptr),
	GameView(nullptr),
	MainWindow(nullptr),
	Quit(false),
	IsPlaying(false),
	Engine(nullptr)
{
}

VEditor::~VEditor()
{
	if (GameView)
		delete(GameView);
	if (SceneView)
		delete(SceneView);
}

bool VEditor::Init(int argc, const char** argv)
{
	Engine = VEngine::GetInstance();

	MainWindow = new VMainWindow();
	if (!MainWindow || !MainWindow->Init())
	{
		return false;
	}
	MainWindow->MakeContextCurrent();	// Set the main window to be the default context

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

	// Init engine at the end
	if (!Engine->Init(argc, argv))
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

	VPanel* panels[] = { MainWindow , GameView, SceneView };
	int panelCount = sizeof(panels) / sizeof(VPanel*);

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
			if (IsPlaying)
			{

			}

			t += dt;
			accumulator -= dt;
		}

		// TODO:: Single frame update code here
		if (IsPlaying)
		{

		}

		// TODO:: Render here

		// Render panels
		for (int i = 0; i < panelCount; i++)
		{
			panels[i]->MakeContextCurrent();

			panels[i]->Render();

			panels[i]->PostRender();

			VRenderer::CheckErrors();
		}

		// Swap buffers
		//for (int i = 0; i < panelCount; i++)
			

		// Poll events
		for (int i = 0; i < panelCount; i++)
			panels[i]->PollEvents();

	}

	return 0;
}