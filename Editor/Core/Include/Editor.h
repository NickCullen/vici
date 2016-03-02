#pragma once

class VEngine;
class VWindow;
class VSceneView;
class VGameView;

class VEditor
{
private:
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