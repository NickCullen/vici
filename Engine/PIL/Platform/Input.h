#pragma once

#include "PIL/PILAPI.h"
#include "InputTypes.h"


class PIL_API VInput
{
private:
	static VInput* CurrentInputContext;		// The current input context to use

	EKeyState Keys[MAX_KEYCOUNT];			// Key buffer

	uint32 ActiveKeyCount;					// The number of active keys for this context

	int MouseX;				
	int MouseY;

	EButtonState MouseButtonStates[MAX_MOUSE_BUTTONS];	// Mouse button states
public:
	VInput();
	~VInput();

	// Returns the current input context
	static VInput* GetInstance();

	// Sets this to the current input context
	void MakeCurrentContext();

	// ------------------------- Keyboard ------------------------------
	// Setters
	void SetKeyDown(EKeyCode key);
	void SetKeyUp(EKeyCode key);
	
	// Returns true if specified key is down for one frame
	bool KeyDown(EKeyCode key) const;

	// Returns true if the specified key is up for one frame
	bool KeyUp(EKeyCode key) const;

	// Returns true if the key is down, will always return true if down
	bool Key(EKeyCode key) const;

	// Returns true if any keys are pressed
	bool Anykey() const;

	// ------------------------ Mouse ---------------------------------
	inline void SetMousePosition(int x, int y) 
	{ 
		MouseX = x;
		MouseY = y;
	}

	inline void GetMousePosition(int& x, int& y) 
	{
		x = MouseX;
		y = MouseY;
	}

	void SetMouseButtonUp(uint32 btn);
	void SetMouseButtonDown(uint32 btn);
	void SetMouseButtonDblClick(uint32 btn);
};
