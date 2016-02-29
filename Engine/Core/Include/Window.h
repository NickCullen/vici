#pragma once

#include "CoreAPI.h"
#include "WindowDefs.h"


class CORE_API VWindow
{
private:
	static bool GLFWInit;

	int Width;
	int Height;

	NativeWindow_t NativeWindow;	// Pointer to native window

	Vkeyfun KeyCallback;					// Pointer to key callback function
	Vmousebuttonfun MouseButtonCallback;	// Pointer to mouse button callback
	Vcursorposfun CursorPosCallback;		// Pointer to mouse move over window callback

	// Internal GLFW callbacksCallbacks
	static void ErrorCallback(int error, const char* desc);
	static void KeyCallbackFn(struct GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseButtonCallbackFn(struct GLFWwindow* window, int button, int action, int mods);
	static void CursorPositionCallbackFn(struct GLFWwindow* window, double xpos, double ypos);

public:

	VWindow(int width, int height, const char* title = "Default Window");
	~VWindow();

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
	* Retursn the size of the context frame buffer
	*/
	void GetFrameBufferSize(int* width, int* height);
};
