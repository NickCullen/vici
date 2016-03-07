#pragma once

#include "CoreAPI.h"
#include "WindowDefs.h"

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
	static bool GLFWInit;
	static int Count;	// Number of windows created

	int WindowID;		// ID of this window (whatever value count is when this window is created)

	NativeWindow_t NativeWindow;	// Pointer to native window

	Vkeyfun KeyCallback;					// Pointer to key callback function
	Vmousebuttonfun MouseButtonCallback;	// Pointer to mouse button callback
	Vcursorposfun CursorPosCallback;		// Pointer to mouse move over window callback
	Vcursorenterfun CursorEnterCallback;	// Pointer to on cursor entered callback
	Vscrollfun ScrollCallback;				// Pointer to mouse wheel scroll callback
	Vdropfun FileDropCallback;				// Pointer to file dop callback

	// Internal GLFW callbacksCallbacks
	static void ErrorCallback(int error, const char* desc);
	static void KeyCallbackFn(struct GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseButtonCallbackFn(struct GLFWwindow* window, int button, int action, int mods);
	static void CursorPositionCallbackFn(struct GLFWwindow* window, double xpos, double ypos);
	static void CursorEnteredCallbackFn(struct GLFWwindow* window, int entered);
	static void ScrollCallbackFn(struct GLFWwindow* window, double x, double y);
	static void FileDropCallbackFn(struct GLFWwindow* window, int count, const char** files);

	static bool Init(); // Initalises library

	/**
	* Overloaded MakeCurrent function for internal use
	*/
	void MakeCurrent(VWindow* ctx);
public:
#ifdef GLEW_MX
	void* glewContext;
	static VWindow* CurrentContext;	// Pointer to the current context
#endif
	void* UserData;					// Pointer to user data for callbacks

	VWindow(int width, int height, const char* title = "Default Window", EWindowMode mode = WINDOW_DEFAULT, VWindow* parent = nullptr);
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
	 * Sets keyboard button callback
	 */
	void SetKeyCallbackFn(Vkeyfun keyFn);

	/**
	 * Sets mouse button callback
	 */
	void SetMouseButtonCallbackFn(Vmousebuttonfun mouseFn);

	/**
	 * Sets function callback for when mouse moves over window
	 */
	void SetCursorPosCallbackFn(Vcursorposfun cursorFn);

	/**
	 * Sets function callback for when mouse enters/leaves window
	 */
	void SetCursorEnteredCallbackFn(Vcursorenterfun cursorFn);
	
	/**
	 * Sets function callback for when mouse wheel scrolls
	 */
	void SetScrollCallbackFn(Vscrollfun scrollFn);

	/**
	 * Sets function callback for when files get drag and dropped onto this window
	 */
	void SetFileDropCallbackFn(Vdropfun dropFn);

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

	/** 
	* Returns the ID of this window
	*/
	inline int GetID() { return WindowID; }
};
