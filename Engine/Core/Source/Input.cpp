#include "Input.h"

// --------------------- Input -----------------------------------------------
VInput::VInput()
	:VSingleton(this),
	CurrentFrame(0),
	ActiveKeyCount(0)
{

}

VInput::~VInput()
{

}


void VInput::SetKeyDown(EKeyCode key)
{
	if (Keys[key].State == KEY_STATE_DOWN || Keys[key].State == KEY_STATE_HELD)
	{
		Keys[key].State = KEY_STATE_HELD;
		Keys[key].Frame = CurrentFrame;
	}
	else
	{
		ActiveKeyCount++;
		Keys[key].State = KEY_STATE_DOWN;
		Keys[key].Frame = CurrentFrame;
	}
}

void VInput::SetKeyUp(EKeyCode key)
{
	ActiveKeyCount--;
	Keys[key].State = KEY_STATE_UP;
	Keys[key].Frame = CurrentFrame;
}

bool VInput::KeyDown(EKeyCode key) const
{
	return (Keys[key].State == KEY_STATE_DOWN && Keys[key].Frame == CurrentFrame);
}

bool VInput::KeyUp(EKeyCode key) const
{
	return (Keys[key].State == KEY_STATE_UP && Keys[key].Frame == CurrentFrame);
}

bool VInput::Key(EKeyCode key) const
{
	return Keys[key].State & (KEY_STATE_HELD | KEY_STATE_DOWN) ? true : false;
}

bool VInput::Anykey() const
{
	return ActiveKeyCount > 0;
}

// --------------------- Key Buttons -----------------------------------------
VButton::VButton(int key, int scancode, int action, int mod)
	:
	Key(key),
	Scancode(scancode),
	Action(action),
	Mod(mod)
{
}

// ---------------------- Mouse Button ---------------------------------------

VMouseButton::VMouseButton(int button, int action, int mods)
	:Button(button),
	Action(action),
	Mods(mods)
{

}

// --------------------- Mouse Info ------------------------------------------

VMouseInfo::VMouseInfo(float x, float y)
	: X(x),
	Y(y)
{

}

// ------------------------ Scroll Info ---------------------------------------

VScrollInfo::VScrollInfo(float x, float y)
	:XOffset(x),
	YOffset(y)
{

}

// ------------------------ Filedrop Info -------------------------------------

VFileDropInfo::VFileDropInfo(int count, const char** paths)
	:Count(count),
	Paths(paths)
{

}