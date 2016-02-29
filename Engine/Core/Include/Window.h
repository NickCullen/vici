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

	Vkeyfun KeyCallback;	// Pointer to key callback function

	// Internal GLFW callbacksCallbacks
	static void ErrorCallback(int error, const char* desc);
	static void KeyCallbackFn(struct GLFWwindow*, int key, int scancode, int action, int mods);
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
	* Retursn the size of the context frame buffer
	*/
	void GetFrameBufferSize(int* width, int* height);
};
