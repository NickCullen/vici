#include "ViciEditor/SceneView.h"
#include "PIL/Platform/Window.h"
#include <stdio.h>
#include "Core/EngineIncludes.h"

VSceneView::VSceneView()
{
}

VSceneView::~VSceneView()
{
}

bool VSceneView::Init()
{
	uint32 mWidth = 0, mHeight = 0;	// Monitor width and height
	VWindow::GetPrimaryMonitorSize(&mWidth, &mHeight);

	//Work out positions
	float x1 = mWidth * 0.25f, x2 = mWidth * 0.5f;
	float y1 = 50, y2 = mHeight * 0.5f - 50;

	Window = CreateWindow((int)x2, (int)y2, "Scene View", WINDOW_DEFAULT);
	Window->SetPosition((int)x1, (int)y1);

	return true;
}

void VSceneView::Render()
{
	VRenderer::GetInstance()->SetViewport(0, 0, GetWidth(), GetHeight());
	VRenderer::GetInstance()->ClearAllBuffers();
	float r = VInput::GetInstance()->Anykey() ? 1.0f : 0.1f;

	VRenderer::GetInstance()->ClearColor(r, 0.1f, 0.1f);

	VEngine::GetInstance()->Render();
}