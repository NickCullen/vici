#pragma once

#include "CoreAPI.h"
#include "InputDef.h"

class CORE_API VButton
{
public:
	int Key;		// Matches V_KEY
	int Scancode;	
	int Action;		// Matches V_KEY_RELEASE/PRESS/REPEAT
	int Mod;

	VButton(int key, int scancode, int action, int mod);
};

class CORE_API VMouseButton
{
public:
	int Button;		// Matches V_MOUSE_BUTTON
	int Action;		// Matches V_KEY_RELEASE/PRESS/REPEAT
	int Mods;		

	VMouseButton(int button, int action, int mods);
};

class CORE_API VMouseInfo
{
public:
	float Y;
	float X;

	VMouseInfo(float x, float y);
};

class CORE_API VScrollInfo
{
public:
	float XOffset;
	float YOffset;

	VScrollInfo(float xOffset, float yOffset);
};

class CORE_API VFileDropInfo
{
public:
	int Count;		// Number of paths dropped here
	const char** Paths;	// Array of pointers containing path names

	VFileDropInfo(int count, const char** paths);
};