#pragma once

#include "InputDef.h"
#include "CoreAPI.h"

class CORE_API VButton
{
public:
	int Key;		// Matches V_KEY
	int Scancode;	
	int Action;		// Matches V_KEY_RELEASE/PRESS/REPEAT
	int Mod;

	VButton(int key, int scancode, int action, int mod);
};
