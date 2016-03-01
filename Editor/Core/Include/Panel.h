#pragma once

class VWindow;
class VButton;
class VMouseButton;
class VMouseInfo;
class VScrollInfo;
class VFileDropInfo;

class VPanel
{
	friend class VEditor;
private:

	// Window callback functions
	static void KeyCallbackFn(VWindow* win, VButton* button);
	static void MouseButtonCallbackFn(VWindow* win, VMouseButton* button);
	static void CursorPosCallbackFn(VWindow* win, VMouseInfo* mi);
	static void CursorEnteredCallbackFn(VWindow* win, bool entered);
	static void ScrollCallback(VWindow* win, VScrollInfo* si);
	static void FileDropped(VWindow* win, VFileDropInfo* fdi);

	// Called by VEditor
	void PostRender();

	void PollEvents();
protected:
	VWindow* Window;

	VWindow* CreateWindow(int width, int height, const char* title, bool border = false);
public:

	VPanel();

	virtual ~VPanel();

	virtual bool Init() = 0;

	virtual void Render();

	// Window event overrides
	virtual void OnKeyPress(VButton* button) {}
	virtual void OnMouseButton(VMouseButton* button) {}
	virtual void OnCursorPosition(VMouseInfo* info) {}
	virtual void OnCursorEnter(bool entered) {}
	virtual void OnMouseScroll(VScrollInfo* info) {}
	virtual void OnFileDropped(VFileDropInfo* info) {}

};