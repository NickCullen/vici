#include "GameView.h"
#include "Window.h"

VGameView::VGameView()
	:Window(nullptr)
{
}

VGameView::~VGameView()
{
}

bool VGameView::Init()
{
	int mWidth = 0, mHeight = 0;	// Monitor width and height
	VWindow::GetPrimaryMonitorSize(&mWidth, &mHeight);

	//Work out positions
	int x1 = mWidth * 0.25f, x2 = mWidth * 0.5f;
	int y1 = mHeight * 0.5f + 50, y2 = mHeight * 0.5f - 100;

	Window = new VWindow(x2, y2, "Game View", false);
	Window->SetPosition(x1, y1);

	return true;
}