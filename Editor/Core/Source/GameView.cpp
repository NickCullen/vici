#include "GameView.h"
#include "Window.h"
#include <stdio.h>
#include "Renderer.h"
#include "Engine.h"
#include "Input.h"


VGameView::VGameView()
	: VPanel()
{
}

VGameView::~VGameView()
{
}

bool VGameView::Init()
{
	uint32 mWidth = 0, mHeight = 0;	// Monitor width and height
	VWindow::GetPrimaryMonitorSize(&mWidth, &mHeight);

	//Work out positions
	int x1 = (int)(mWidth * 0.25f), x2 = (int)(mWidth * 0.5f);
	int y1 = (int)(mHeight * 0.5f + 50), y2 = (int)(mHeight * 0.5f - 100);

	Window = CreateWindow(x2, y2, "Game View", WINDOW_DEFAULT);
	Window->SetPosition(x1, y1);

	return true;
}

void VGameView::Render()
{
	VRenderer::GetInstance()->SetViewport(0, 0, GetWidth(), GetHeight());
	VRenderer::GetInstance()->ClearAllBuffers();

	float r = VInput::GetInstance()->Anykey() ? 1.0f : 0.1f;

	VRenderer::GetInstance()->ClearColor(r, 0.1f, 0.1f);
	
	VEngine::GetInstance()->Render();
}