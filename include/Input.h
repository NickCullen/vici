#ifndef INPUT_H
#define INPUT_H

#include "PlatformDefinitions.h"
#include "glm.h"

/**
* static class for reading input
*/

class Input
{
private:
	
public:
	/**
	* Unused constructor (Static class)
	*/
	Input();

	/** 
	* Unused destructor (Static class)
	*/
	~Input();

	/**
	* Checks to see if the specified (GLFW defined)
	* key is pressed 
	* @param key The key to check if pressed
	* @return bool true if pressed
	*/
	static bool KeyDown(uint32 key);

	/**
	* Checks to see if the specified (GLFW defined)
	* key is released
	* @param key The key to check if released
	* @return bool true if released
	*/
	static bool KeyUp(uint32 key);

	/**
	* Returns the status of the key
	* @param key The key to check status
	* @return bool true pressed false if not
	*/
	static bool Key(uint32 key);

	/**
	* Returns the mouse position
	* @return vec2 containing mouse position
	*/
	static glm::vec2 MousePosition();
};

#endif