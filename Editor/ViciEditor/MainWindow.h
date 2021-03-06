#pragma once

#include "Core/Engine/Singleton.h"
#include "Panel.h"

class VWindow;

class VICI_EDITOR_API VMainWindow : public VSingleton<VMainWindow>, public VPanel
{
private:

public:

	VMainWindow();
	~VMainWindow();

	bool Init() override;

	void Render() override;

	inline VWindow* GetWindow() { return Window; }
};