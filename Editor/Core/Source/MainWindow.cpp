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

	Window = new VWindow();
	if (!Window)
		return false;
	Window->SetSize(sw, sh);
	Window->SetTitle("Vici Editor");
	Window->SetMode(WINDOW_FULLSCREEN_WINDOWED);

	if (!Window->CreateNewWindow())
	{
		delete(Window);
		Window = nullptr;
		return false;
	}


	return true;
}

void VMainWindow::Render()
{
	VRenderer::GetInstance()->SetViewport(0, 0, GetWidth(), GetHeight());
	VRenderer::GetInstance()->ClearAllBuffers();
	VRenderer::GetInstance()->ClearColor(0.1f, 0.1f, 0.1f);

	VEngine::GetInstance()->Render();
}