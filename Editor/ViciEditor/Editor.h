#pragma once

#include "ViciEditor/ViciEditorAPI.h"

class VEngine;
class VMainWindow;
class VSceneView;
class VGameView;

class VICI_EDITOR_API VEditor
{
private:
	VMainWindow* MainWindow;

	VEngine* Engine;

	VSceneView* SceneView;
	VGameView* GameView;

	bool Quit;
	bool IsPlaying;

public:
	VEditor();

	~VEditor();

	bool Init(int argc, const char** argv);

	int Run();
};