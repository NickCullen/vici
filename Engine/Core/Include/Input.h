#pragma once

#include "CoreAPI.h"
#include "InputDef.h"
#include "Singleton.h"
#include "KeyCode.h"
#include "VTypes.h"
#include "Vector2.h"

class CORE_API VInput : public VSingleton<VInput>
{
	enum EKeyState
	{
		KEY_STATE_NONE,
		KEY_STATE_DOWN = 1,
		KEY_STATE_UP = 2,
		KEY_STATE_HELD = 4
	};

	struct CORE_API VKeyInfo
	{
		EKeyState State;	// The state of this key
		uint32 Frame;		// What frame this key was down

		VKeyInfo()
			:State(KEY_STATE_NONE),
			Frame(0) {}
	};

private:
	VKeyInfo Keys[MAX_KEYCOUNT];

	uint32 CurrentFrame;	// The current frame count

	uint32 ActiveKeyCount;	// The number of active keys

	Vector2f MousePosition;	
public:
	VInput();
	~VInput();

	// ------------------------- Keyboard ------------------------------
	// Setters
	inline void SetCurrentFrame(uint32 frame) { CurrentFrame = frame; }
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
	inline void SetMousePosition(Vector2f& pos) { MousePosition = pos; }
	inline const Vector2f& GetMousePosition() { return MousePosition; }

};
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