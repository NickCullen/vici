#pragma once

class VWindow;

class VGameView
{
	friend class VEditor;
private:
	VWindow* Window;

public:
	VGameView();
	~VGameView();

	
	bool Init();
};

