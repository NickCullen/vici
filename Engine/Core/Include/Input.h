#ifndef INPUT_H
#define INPUT_H

#include "CoreAPI.h"
#include "Singleton.h"

#define _Input Singleton<Input>::Instance()

/**
* Singleton class for reading input
*/

class CORE_API Input : public Singleton<Input>
{
private:
	
public:
	/**
	* Default constructor
	*/
	Input();

	/** 
	* Default destructor 
	*/
	~Input();

	/**
	* Checks to see if the specified (GLFW defined)
	* key is pressed 
	* @param key The key to check if pressed
	* @return bool true if pressed
	*/
	bool KeyDown(SDL_Keycode key);

	/**
	* Checks to see if the specified (GLFW defined)
	* key is released
	* @param key The key to check if released
	* @return bool true if released
	*/
	bool KeyUp(SDL_Keycode key);

	/**
	* Returns the status of the key
	* @param key The key to check status
	* @return bool true pressed false if not
	*/
	bool Key(SDL_Keycode key);

	/**
	* Returns the mouse position
	* @return vec2 containing mouse position
	*/
	class Vector2f MousePosition();
};

#endif