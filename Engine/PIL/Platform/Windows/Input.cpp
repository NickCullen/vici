#include "PIL/Platform/Input.h"

// Static init
VInput* VInput::CurrentInputContext = nullptr;

// --------------------- Input -----------------------------------------------
VInput::VInput()
	:ActiveKeyCount(0),
	MouseX(0),
	MouseY(0)
{

}

VInput::~VInput()
{

}

VInput* VInput::GetInstance() 
{ 
	return CurrentInputContext; 
}

void VInput::MakeCurrentContext()
{
	CurrentInputContext = this; 
}



// ---------------------------------------------- Keyboard -----------------------------------------
void VInput::SetKeyDown(EKeyCode key)
{
	if (Keys[key] == KEY_STATE_DOWN || Keys[key] == KEY_STATE_HELD)
	{
		Keys[key] = KEY_STATE_HELD;
	}
	else
	{
		ActiveKeyCount++;
		Keys[key] = KEY_STATE_DOWN;
	}
}

void VInput::SetKeyUp(EKeyCode key)
{
	ActiveKeyCount--;
	Keys[key] = KEY_STATE_UP;
}

bool VInput::KeyDown(EKeyCode key) const
{
	return (Keys[key] == KEY_STATE_DOWN);
}

bool VInput::KeyUp(EKeyCode key) const
{
	return (Keys[key] == KEY_STATE_UP);
}

bool VInput::Key(EKeyCode key) const
{
	return Keys[key] & (KEY_STATE_HELD | KEY_STATE_DOWN) ? true : false;
}

bool VInput::Anykey() const
{
	return ActiveKeyCount > 0;
}

// --------------------------------- Mouse Buttons ----------------------------
void VInput::SetMouseButtonUp(uint32 btn)
{
	MouseButtonStates[btn] = BUTTON_STATE_UP;

}

void VInput::SetMouseButtonDown(uint32 btn)
{
	MouseButtonStates[btn] = BUTTON_STATE_DOWN;
}

void VInput::SetMouseButtonDblClick(uint32 btn)
{
	MouseButtonStates[btn] = BUTTON_STATE_DBL;
}
