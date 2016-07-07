#include "ViciEditor/MainWindow.h"
#include "PIL/Platform/Window.h"
#include "Core/EngineIncludes.h"

VMainWindow::VMainWindow()
	:VSingleton(this)
{
	
}

VMainWindow::~VMainWindow()
{

}

bool VMainWindow::Init()
{
	uint32 sw, sh;
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
	float r = VInput::GetInstance()->Anykey() ? 1.0f : 0.1f;

	VRenderer::GetInstance()->ClearColor(r, 0.1f, 0.1f);

	VEngine::GetInstance()->Render();
}