#pragma once

#include "CoreAPI.h"
#include "VTypes.h"

// Forward decl
struct NativeWindow_t;
class VInput;

/**
 * Enum defining how to open a window
 */
enum EWindowMode
{
	WINDOW_DEFAULT,
	WINDOW_FULLSCREEN_WINDOWED,
	WINDOW_FULLSCREEN_BORDERLESS
};


class CORE_API VWindow
{
private:
	static uint32 Count;	// Number of windows created
	static bool Initialized;	// Window library initialized

	uint32 WindowID;		// ID of this window (whatever value count is when this window is created)

	NativeWindow_t* NativeWindow;	// Pointer to native window

	VInput* Input;			// The input context for this window

	/**
	* Overloaded MakeCurrent function for internal use
	*/
	void MakeCurrent(VWindow* ctx);

	/**
	 * Crate window
	 */
	bool CreateNewWindow(uint32 width, uint32 height, const char* title, EWindowMode mode, VWindow* parent);

	/**
	 * Initializes windowing library
	 */
	static bool Initialize();
public:

	static VWindow* CurrentContext;	// Pointer to the current context

	void* UserData;					// Pointer to user data for callbacks

	VWindow(uint32 width, uint32 height, const char* title = "Default Window", EWindowMode mode = WINDOW_DEFAULT, VWindow* parent = nullptr);
	~VWindow();

	/**
	 * Positions the window
	 */
	void SetPosition(int xPos, int yPos);

	/**
	* Sets current opengl context for rendering 
	*/
	void MakeCurrent();	

	/**
	* Queries window to see if it should close or not
	*/
	bool ShouldClose();

	/**
	 * Tell the window it should close
	 */
	void SignalShouldClose();

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
	* Terminates all windows
	*/
	static void TerminateAll();

	/**
	* Returns the size of the window
	*/
	void GetWindowSize(int* width, int* height);

	/**
	* Returns the size of the context frame buffer (may differ from window size)
	*/
	void GetFrameBufferSize(int* width, int* height);

	/**
	 * Returns the max size of the screen
	 */
	static void GetPrimaryMonitorSize(int* width, int* height);

	/**
	 * Hints to set before creating windows
	 */
	static void SetBorderHint(bool show);

	// Getters
	inline int GetID() { return WindowID; }
	inline VInput* GetInput() { return Input; }
	inline NativeWindow_t* GetNativeWindow() { return NativeWindow; }
};
