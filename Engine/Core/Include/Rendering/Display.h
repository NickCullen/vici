#ifndef DISPLAY_H
#define DISPLAY_H

#include "CoreAPI.h"
#include "Singleton.h"
#include "PlatformDefinitions.h"
#include "glm.h"
#include "Serialization.h"

#define _Display Singleton<Display>::Instance()

/**
* Display class contains information of the surface that the engine
* is being rendered on.
*/

class CORE_API Display : public Singleton<Display>, ISerializable
{
private:
	int32 _context_width; /**< The width of the current window (renderable area)*/
	int32 _context_height; /**< The height of the current window (renderable area) */

	int32 _screen_width; /**< The width of the screen (i.e. the physical monitor) */
	int32 _screen_height; /**< The height of the screen (i.e. the physical monitor) */

	VRenderContext* _render_context; /**< The window that is used to render the engine */

	int32 _refresh_rate; /**< Refresh rate of the monitor */
	
	bool _fullscreen;   /**< Flag for full screen window */
	
	bool _has_focus;	/**< Flag signifying if the window with the program running has focus or not */
	
    std::string _title;       /**< Title of display */
	
public:
	/**
	* Default constructor 
	*/
	Display();

	/** 
	* Default destructor
	*/
	~Display();
	
	virtual void Serialize(ArchiveOut& archive);
	virtual void Deserialize(ArchiveIn& archive);
	
	/**
	* Creates display using the saved preferences
	*/
	void Init();
	
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
		return _context_height;
	}


	/**
	* Gets the width of the window
	* @return integer representing the width of the window
	*/
	inline int32 Width()
	{
		return _context_width;
	}

	/**
	* Calculates the aspect reation of the current window
	* @return float containing aspect ratio
	*/
	inline float AspectRatio()
	{
		//prevent division  by 0
		if (glm::epsilon<float>() > (float)_context_height) return 1.0f;
		return (float)_context_width / (float)_context_height;
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
		return _render_context;
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