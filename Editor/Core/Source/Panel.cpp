#include "Panel.h"
#include "Window.h"

VPanel::VPanel()
	:Window(nullptr)
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
	//VWindow::SetBorderHint(border);		commented out for now

	Window = new VWindow(width, height, title, false);	// Never have a full screen panel
	Window->UserData = this;	// Make sure we store a reference to his

	// Set callbacks
	Window->SetKeyCallbackFn(VPanel::KeyCallbackFn);
	Window->SetMouseButtonCallbackFn(VPanel::MouseButtonCallbackFn);
	Window->SetCursorPosCallbackFn(VPanel::CursorPosCallbackFn);
	Window->SetCursorEnteredCallbackFn(VPanel::CursorEnteredCallbackFn);
	Window->SetScrollCallbackFn(VPanel::ScrollCallback);
	Window->SetFileDropCallbackFn(VPanel::FileDropped);

	return Window;
}

void VPanel::KeyCallbackFn(VWindow* win, VButton* button)
{
	VPanel* panel = (VPanel*)win->UserData;
	if (panel)
		panel->OnKeyPress(button);
}
void VPanel::MouseButtonCallbackFn(VWindow* win, VMouseButton* button)
{
	VPanel* panel = (VPanel*)win->UserData;
	if (panel)
		panel->OnMouseButton(button);
}
void VPanel::CursorPosCallbackFn(VWindow* win, VMouseInfo* mi)
{
	VPanel* panel = (VPanel*)win->UserData;
	if (panel)
		panel->OnCursorPosition(mi);
}
void VPanel::CursorEnteredCallbackFn(VWindow* win, bool entered)
{
	VPanel* panel = (VPanel*)win->UserData;
	if (panel)
		panel->OnCursorEnter(entered);
}
void VPanel::ScrollCallback(VWindow* win, VScrollInfo* si)
{
	VPanel* panel = (VPanel*)win->UserData;
	if (panel)
		panel->OnMouseScroll(si);
}
void VPanel::FileDropped(VWindow* win, VFileDropInfo* fdi)
{
	VPanel* panel = (VPanel*)win->UserData;
	if (panel)
		panel->OnFileDropped(fdi);
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