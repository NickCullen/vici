#pragma once

#include "CoreAPI.h"
#include "VTypes.h"
#include "VString.h"

// Forward decl
struct NativeWindow_t;
class VInput;

/**
 * Enum defining how to open a window
 */
enum EWindowMode
{
	WINDOW_DEFAULT,
	WINDOW_DEFAULT_NO_TOPBAR,
	WINDOW_FULLSCREEN_WINDOWED,
	WINDOW_FULLSCREEN_BORDERLESS
};


class CORE_API VWindow
{
private:
	static uint32 Count;		// Number of windows created
	static bool Initialized;	// Window library initialized

	// ID Of this window
	uint32 WindowID;

	// Struct containing native windows
	NativeWindow_t* NativeWindow;

	// Input context for this window
	VInput* Input;		

	// Title of the window
	VString Title;

	// Parent window (this window will share its render context
	VWindow* Parent;

	// position
	uint32 X;
	uint32 Y;

	// Size
	uint32 Width;			
	uint32 Height;

	// How this window is to be displayed
	EWindowMode Mode;

	// Fullscreen flag
	bool FullScreen;

	// Close flag
	bool CloseFlag;

	/**
	* Overloaded MakeCurrent function for internal use
	*/
	void MakeCurrent(VWindow* ctx);

	/**
	 * Initializes windowing library
	 */
	static bool Initialize();

	/**
	 * Handles the switch of Mode when creating window
	 */
	bool HandleMode();

	/**
	 * Updates the natively kept window rect
	 */
	void UpdateWindowRect();

public:

	static VWindow* CurrentContext;	// Pointer to the current context

	void* UserData;					// Pointer to user data for callbacks

	VWindow();
	~VWindow();

	/**
	* Crate opengl window
	*/
	bool CreateNewWindow();

	/**
	* Sets current opengl context for rendering 
	*/
	void MakeCurrent();	

	/**
	* Swaps back buffers
	*/
	void Swapbuffers();

	/**
	* Polls window events
	*/
	void PollEvents();

	/**
	* Closes this window
	*/
	void Close();

	/**
	* Queries window to see if it should close or not
	*/
	bool ShouldClose();

	/**
	* Tell the window it should close
	*/
	void SignalClose();

	/**
	* Returns the size of the window
	*/
	void GetWindowSize(uint32* width, uint32* height);

	/**
	 * Returns the max size of the screen
	 */
	static void GetPrimaryMonitorSize(uint32* width, uint32* height);

	/**
	 * Returns true if the window is open
	 */
	bool IsOpen();
	
	// Setters
	void SetPosition(uint32 xPos, uint32 yPos, bool post = true);
	void SetSize(uint32 width, uint32 height, bool post = true);
	void SetTitle(const VString& title, bool post = true);
	void SetMode(EWindowMode mode);
	void SetParent(VWindow* parent);
	void SetCloseFlag(bool flag);

	// Getters
	inline int GetID() { return WindowID; }
	inline VInput* GetInput() { return Input; }
	inline NativeWindow_t* GetNativeWindow() { return NativeWindow; }
	inline uint32 GetWidth() { return Width; }
	inline uint32 GetHeight() { return Height; }
};
