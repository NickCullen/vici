#pragma once

#include "InputTypes.h"


class CORE_API VInput
{
	/**
	 * Internally kept, stores per frame keyboard
	 * key info
	 */
	struct CORE_API VKeyInfo
	{
		EKeyState State;	// The state of this key
		uint32 Frame;		// What frame this key was down

		VKeyInfo()
			:State(KEY_STATE_NONE),
			Frame(0) {}
	};

	/**
	 * Internally kept, stores per frame mouse button info
	 */
	struct CORE_API VButtonInfo
	{
		EButtonState State;
		uint32 Frame;

		VButtonInfo()
			:State(BUTTON_STATE_NONE),
			Frame(0) {}
	};

private:
	static VInput* CurrentInputContext;		// The current input context to use

	VKeyInfo Keys[MAX_KEYCOUNT];			// Key buffer

	uint32 ActiveKeyCount;					// The number of active keys for this context

	Vector2f MousePosition;					// The mouse position for this context

	VButtonInfo MouseButtonStates[MAX_MOUSE_BUTTONS];	// Mouse button states

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
	inline void SetMousePosition(Vector2f& pos) { MousePosition = pos; }
	inline const Vector2f& GetMousePosition() { return MousePosition; }
	void SetMouseButtonUp(uint32 btn);
	void SetMouseButtonDown(uint32 btn);
	void SetMouseButtonDblClick(uint32 btn);
};
