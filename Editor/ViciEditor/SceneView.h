#pragma once

#include "Panel.h"

class VICI_EDITOR_API VSceneView : public VPanel
{
private:
	
public:
	VSceneView();
	~VSceneView();

	bool Init() override;

	void Render() override;
};

