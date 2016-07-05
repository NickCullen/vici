#pragma once

// Includes
#include "KeyCode.h"
#include "PIL/DataTypes/PlatformTypes.h"

// Constants
static const uint8 MAX_MOUSE_BUTTONS = 3;

// Enums
enum EKeyState
{
	KEY_STATE_NONE,
	KEY_STATE_DOWN = 1,
	KEY_STATE_UP = 2,
	KEY_STATE_HELD = 4
};

enum EButtonState
{
	BUTTON_STATE_NONE,
	BUTTON_STATE_DOWN,
	BUTTON_STATE_UP,
	BUTTON_STATE_DBL
};

