#include "MainWindow.h"
#include "Window.h"
#include "Renderer.h"
#include "Engine.h"

VMainWindow::VMainWindow()
	:VSingleton(this)
{
	
}

VMainWindow::~VMainWindow()
{

}

bool VMainWindow::Init()
{
	int sw, sh;
	VWindow::GetPrimaryMonitorSize(&sw, &sh);

	Window = new VWindow(sw, sh, "Vici Editor", WINDOW_FULLSCREEN_WINDOWED);
	Window->SetPosition(0, 30);
	if (!Window)
		return false;
	return true;
}

void VMainWindow::Render()
{
	VRenderer::GetInstance()->SetViewport(0, 0, GetWidth(), GetHeight());
	VRenderer::GetInstance()->ClearAllBuffers();
	VRenderer::GetInstance()->ClearColor(0.1f, 0.1f, 0.1f);

	VEngine::GetInstance()->Render();
}