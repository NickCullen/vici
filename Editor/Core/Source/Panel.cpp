#include "Panel.h"
#include "Window.h"
#include "MainWindow.h"

VPanel::VPanel()
	:Window(nullptr),
	Width(0),
	Height(0)
{

}

VPanel::~VPanel()
{
	if (Window)
		delete(Window);
	Window = nullptr;
}

VWindow* VPanel::CreateWindow(int width, int height, const char* title, bool border)
{
	// Make sure appropriate hints are set
	VWindow::SetBorderHint(border);		

	// Share the context of the main window
	Window = new VWindow();
	if (!Window)
		return false;

	Window->SetParent(VMainWindow::GetInstance()->GetWindow());
	Window->SetSize(width, height);
	Window->SetTitle("Vici Editor");
	Window->SetMode(WINDOW_DEFAULT);
	Window->UserData = this;

	if (!Window->CreateNewWindow())
	{
		delete(Window);
		Window = nullptr;
		return false;
	}
	
	Window->UserData = this;	// Make sure we store a reference to his

	// Set vars
	Width = width;
	Height = height;

	return Window;
}

void VPanel::PostRender()
{
	if (Window) Window->Swapbuffers();
}

void VPanel::PollEvents()
{
	if (Window) Window->PollEvents();
}

void VPanel::MakeContextCurrent()
{
	if (Window) Window->MakeCurrent();

}

int VPanel::GetWidth()
{
	if (Window != nullptr)
		Window->GetFrameBufferSize(&Width, &Height);
	return Width;
}

int VPanel::GetHeight()
{
	if (Window != nullptr)
		Window->GetFrameBufferSize(&Width, &Height);
	return Height;
}