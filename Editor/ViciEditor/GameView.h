#pragma once

#include "Panel.h"

class VICI_EDITOR_API VGameView : public VPanel
{
private:

public:
	VGameView();
	~VGameView();

	
	bool Init() override;

	void Render() override;
};

