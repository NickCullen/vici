#pragma once

class VWindow;

class VSceneView
{
	friend class VEditor;
private:
	VWindow* Window;
public:
	VSceneView();
	~VSceneView();

	bool Init();

	
};

