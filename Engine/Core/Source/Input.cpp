#include "Input.h"

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