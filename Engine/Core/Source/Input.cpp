#include "Input.h"
#include "Engine.h"

// Static init
VInput* VInput::CurrentInputContext = nullptr;

// --------------------- Input -----------------------------------------------
VInput::VInput()
	:ActiveKeyCount(0),
	MousePosition(0.0f, 0.0f)
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
	if (Keys[key].State == KEY_STATE_DOWN || Keys[key].State == KEY_STATE_HELD)
	{
		Keys[key].State = KEY_STATE_HELD;
		Keys[key].Frame = VEngine::GetInstance()->GetCurrentFrame();
	}
	else
	{
		ActiveKeyCount++;
		Keys[key].State = KEY_STATE_DOWN;
		Keys[key].Frame = VEngine::GetInstance()->GetCurrentFrame();;
	}
}

void VInput::SetKeyUp(EKeyCode key)
{
	ActiveKeyCount--;
	Keys[key].State = KEY_STATE_UP;
	Keys[key].Frame = VEngine::GetInstance()->GetCurrentFrame();;
}

bool VInput::KeyDown(EKeyCode key) const
{
	return (Keys[key].State == KEY_STATE_DOWN && Keys[key].Frame == VEngine::GetInstance()->GetCurrentFrame());
}

bool VInput::KeyUp(EKeyCode key) const
{
	return (Keys[key].State == KEY_STATE_UP && Keys[key].Frame == VEngine::GetInstance()->GetCurrentFrame());
}

bool VInput::Key(EKeyCode key) const
{
	return Keys[key].State & (KEY_STATE_HELD | KEY_STATE_DOWN) ? true : false;
}

bool VInput::Anykey() const
{
	return ActiveKeyCount > 0;
}

// --------------------------------- Mouse Buttons ----------------------------
void VInput::SetMouseButtonUp(uint32 btn)
{
	MouseButtonStates[btn].State = BUTTON_STATE_UP;
	MouseButtonStates[btn].Frame = VEngine::GetInstance()->GetCurrentFrame();;

}

void VInput::SetMouseButtonDown(uint32 btn)
{
	MouseButtonStates[btn].State = BUTTON_STATE_DOWN;
	MouseButtonStates[btn].Frame = VEngine::GetInstance()->GetCurrentFrame();;
}

void VInput::SetMouseButtonDblClick(uint32 btn)
{
	MouseButtonStates[btn].State = BUTTON_STATE_DBL;
	MouseButtonStates[btn].Frame = VEngine::GetInstance()->GetCurrentFrame();;
}
