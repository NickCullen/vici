#include "SceneView.h"
#include "Window.h"

VSceneView::VSceneView()
{
}

VSceneView::~VSceneView()
{
}

bool VSceneView::Init()
{
	int mWidth = 0, mHeight = 0;	// Monitor width and height
	VWindow::GetPrimaryMonitorSize(&mWidth, &mHeight);

	//Work out positions
	int x1 = mWidth * 0.25f, x2 = mWidth * 0.5f;
	int y1 = 50, y2 = mHeight * 0.5f - 50;

	Window = CreateWindow(x2, y2, "Scene View", false);
	Window->SetPosition(x1, y1);

	return true;
}