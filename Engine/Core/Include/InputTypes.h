#pragma once

// Includes
#include "CoreAPI.h"
#include "KeyCode.h"
#include "VTypes.h"
#include "Vector2.h"

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

