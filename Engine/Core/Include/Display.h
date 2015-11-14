#ifndef DISPLAY_H
#define DISPLAY_H

#include "CoreAPI.h"
#include "Singleton.h"
#include "PlatformDefinitions.h"
#include "glm.h"

#define _Display Singleton<Display>::Instance()

/**
* Structure containing info of the current 
* window. Returns the width and height.
*/

struct CORE_API DisplayInfo
{
	int32 _w;
	int32 _h;

	/**
	* Constructor to take the width
	* and height to set
	*/
	DisplayInfo(int32 w, int32 h)
	{
		_w = w; _h = h;
	}

};

/**
* Display class singleton containing the width and height
* of the display, also in charge of the VWindow reference. 
*/

class CORE_API Display : public Singleton<Display>
{
private:
	int32 _window_width; /**< The width of the current window (renderable area)*/
	int32 _window_height; /**< The height of the current window (renderable area) */

	int32 _screen_width; /**< The width of the screen (i.e. the physical monitor) */
	int32 _screen_height; /**< The height of the screen (i.e. the physical monitor) */

	VWindow* _window; /**< The window that is used to render the engine */

	int32 _refresh_rate; /**< Refresh rate of the monitor */

	bool _has_focus;	/**< Flag signifying if the window with the program running has focus or not */
public:
	/**
	* Default constructor 
	*/
	Display();

	/** 
	* Default destructor
	*/
	~Display();

	/**
	* Used to load and initialize the display 
	* from the display xml file found in the 
	* settings folder of the project
	*/
	void Init(char* cwd);

	/**
	* Creates a DisplayInfo structor and returns it
	* @return DisplayInfo structure holding information about the current display 
	*/
	inline DisplayInfo GetInfo()
	{
		return DisplayInfo(_window_width, _window_height);
	}

	/**
	* Gets the height of the window
	* @return integer representing the height of the window
	*/
	inline int32 Height()
	{
		return _window_height;
	}


	/**
	* Gets the width of the window
	* @return integer representing the width of the window
	*/
	inline int32 Width()
	{
		return _window_width;
	}

	/**
	* Calculates the aspect reation of the current window
	* @return float containing aspect ratio
	*/
	inline float AspectRatio()
	{
		//prevent division  by 0
		if (glm::epsilon<float>() > (float)_window_height) return 1.0f;
		return (float)_window_width / (float)_window_height;
	}

	/**
	* Sets the size of the display with an optional third paramter
	* to resize the window. 
	* @param w The width of the window
	* @param h The height of the window
	* @param force_window_resize set to true to resize the window
	*/
	void SetSize(int32 w, int32 h, bool force_window_resize = false);

	/**
	* Gets the window (may be NULL)
	* @return Pointer to the window that is open (May be null)
	*/
	inline VWindow* Window()
	{
		return _window;
	}

	/**
	* Called by os when the window is resized
	* @param win Pointer to the window being resized
	* @param w The new width of the window
	* @param h The new height of the window
	*/
	static void OnResize(VWindow* win, int32 w, int32 h);

	/**
	* gets the refresh rate of the monitor
	* @return Integer specifying the refresh rate of the monitor
	*/
	inline int32 RefreshRate(){ return _refresh_rate; }

	/**
	* Getter for has focus
	* @return Returns true if window has focus false otherwise
	*/
	inline bool HasFocus(){ return _has_focus; }

	/**
	* Setter for has focus
	* @param value sets _has_focus to value
	*/
	inline void SetHasFocus(bool value){ _has_focus = value; }
};

#endif