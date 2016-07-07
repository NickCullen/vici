#pragma once

#include "PIL/DataTypes/PlatformTypes.h"

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
	// Called by VEditor
	void MakeContextCurrent();	// Set render target
	void PostRender();

	void PollEvents();
protected:
	VWindow* Window;

	uint32 Width;
	uint32 Height;

	VWindow* CreateWindow(int width, int height, const char* title, bool border = false);
public:

	VPanel();

	virtual ~VPanel();

	virtual bool Init() = 0;

	virtual void Render() {}

	// Getters
	int GetWidth();
	int GetHeight();
};