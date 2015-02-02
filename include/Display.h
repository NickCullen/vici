#ifndef DISPLAY_H
#define DISPLAY_H

#include "PlatformDefinitions.h"

/**
* Structure containing info of the current 
* window. Returns the width and height.
*/

struct DisplayInfo
{
	int _w; /**< The width of the display */
	int _h; /**< The height of the display */

	/**
	* Constructor to take the width
	* and height to set
	*/
	DisplayInfo(int w, int h)
	{
		_w = w; _h = h;
	}

};

/**
* Static Display class containing the width and height
* of the display, also in charge of the VWindow reference. 
*/

class Display
{
private:
	static int _w; /**< The width of the current window */
	static int _h; /**< The height of the current window */

	static VWindow* _window; /**< The window that is used to render the engine */

	static int _refresh_rate; /**< Refresh rate of the monitor */

public:
	/**
	* Unused constructor (Static class)
	*/
	Display();

	/** 
	* Unused destructor (Static class)
	*/
	~Display();

	/**
	* Used to load and initialize the display 
	* from the display xml file found in the 
	* settings folder of the project
	*/
	static void Init(char* cwd);

	/**
	* Creates a DisplayInfo structor and returns it
	* @return DisplayInfo structure holding information about the current display 
	*/
	static inline DisplayInfo GetInfo()
	{
		return DisplayInfo(_w, _h);
	}

	/**
	* Calculates the aspect reation of the current window
	* @return float containing aspect ratio
	*/
	static inline float AspectRatio()
	{
		return (float)_w / (float)_h;
	}

	/**
	* Sets the size of the display with an optional third paramter
	* to resize the window. 
	* @param w The width of the display
	* @param h The height of the display
	* @param force_window_resize set to true to resize the window
	*/
	static void SetSize(int w, int h, bool force_window_resize = false);

	/**
	* Gets the window (may be NULL)
	* @return Pointer to the window that is open (May be null)
	*/
	static inline VWindow* Window()
	{
		return _window;
	}

	/**
	* Called by os when the window is resized
	* @param win Pointer to the window being resized
	* @param w The new width of the window
	* @param h The new height of the window
	*/
	static void OnResize(VWindow* win, int w, int h);

	/**
	* gets the refresh rate of the monitor
	* @return Integer specifying the refresh rate of the monitor
	*/
	inline static int RefreshRate(){ return _refresh_rate; }
};

#endif