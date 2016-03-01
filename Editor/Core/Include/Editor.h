#pragma once

class VWindow;
class VSceneView;
class VGameView;

class VEditor
{
private:
	VSceneView* SceneView;
	VGameView* GameView;

	bool Quit;

public:
	VEditor();

	~VEditor();

	bool Init(int argc, int argv);

	int Run();
};