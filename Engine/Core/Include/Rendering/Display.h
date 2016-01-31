#ifndef DISPLAY_H
#define DISPLAY_H

#include "CoreAPI.h"
#include "Singleton.h"
#include "Serialization.h"
#include "Mathf.h"

#define _Display Singleton<Display>::Instance()

/**
* Display class contains information of the surface that the engine
* is being rendered on.
*/

class CORE_API Display : public Singleton<Display>
{
private:
	
	
public:

	int32 ContextWidth; /**< The width of the current window (renderable area)*/
	int32 ContextHeight; /**< The height of the current window (renderable area) */

	int32 ScreenWidth; /**< The width of the screen (i.e. the physical monitor) */
	int32 ScreenHeight; /**< The height of the screen (i.e. the physical monitor) */

	VRenderContext* RenderContext; /**< The window that is used to render the engine */

	int32 RefreshRate; /**< Refresh rate of the monitor */

	bool bFullscreen;   /**< Flag for full screen window */

	bool bHasFocus;	/**< Flag signifying if the window with the program running has focus or not */

	std::string Title;       /**< Title of display */

	/**
	* Default constructor 
	*/
	Display();

	/** 
	* Default destructor
	*/
	~Display();

	template<class Archive>
	void serialize(Archive& ar)
	{
		_SERIALIZE_VAR(Title, ar)
		_SERIALIZE_VAR(ContextWidth, ar)
		_SERIALIZE_VAR(ContextHeight, ar)
		_SERIALIZE_VAR(bFullscreen, ar)
	}

	/**
	* Creates display using the saved preferences
	*/
	bool Init();
	
	/**
	* Used to set the context of the display
	* @param context The new platform context object to be set
	*/
	void SetRenderContext(VRenderContext* context);
	
	/**
	* Gets the height of the window
	* @return integer representing the height of the window
	*/
	inline int32 Height()
	{
		return ContextHeight;
	}


	/**
	* Gets the width of the window
	* @return integer representing the width of the window
	*/
	inline int32 Width()
	{
		return ContextWidth;
	}

	/**
	* Calculates the aspect reation of the current window
	* @return float containing aspect ratio
	*/
	inline float AspectRatio()
	{
		//prevent division  by 0
		if (Mathf::Epsilon > (float)ContextHeight) return 1.0f;
		return (float)ContextWidth / (float)ContextHeight;
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
	* Gets the platform render context object (may be NULL)
	* @return Pointer to the context that is in use (May be null)
	*/
	inline VRenderContext* GetRenderContext()
	{
		return RenderContext;
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
	inline int32 GetRefreshRate(){ return RefreshRate; }

	/**
	* Getter for has focus
	* @return Returns true if window has focus false otherwise
	*/
	inline bool HasFocus(){ return bHasFocus; }

	/**
	* Setter for has focus
	* @param value sets _has_focus to value
	*/
	inline void SetHasFocus(bool value){ bHasFocus = value; }
	
	/**
	* Function to call to clear the renderable area on display
	*/
	void ClearRenderArea();
	
	/**
	* Function to call to swap back render buffer 
	*/
	void SwapBuffers();
};

#endif