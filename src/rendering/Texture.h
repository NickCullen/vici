#ifndef V_TEXTURE
#define V_TEXTURE

#include "PlatformDefinitions.h"
#include "rapidxml\rapidxml.hpp"

/** 
* Texture asset (works in the same way Mesh does)
* except it isn't a component
*/

class Texture 
{
private:
	int _width; /**< Width of the texture */
	int _height; /**< Height of the texture */
	int _comp; /**< Number of components the texture has i.e. grey = 1, greyalpha = 2, rgb = 3, rgba = 4 */

	uint32 _texture; /**< Texture reference in opengl */

	char* _id; /**< ID of sampler in the shader */

	/**
	* Returns the format in enum type given the
	* specified format string (from xml)
	* @param format The string format of the image can be one of the following - "grey, greyalpha, rgb, rgba"
	* @return integer reference the stb enum of the format
	*/
	int GetFormat(char* format);

public:
	/** 
	* Default ctor
	*/
	Texture();

	/**
	* Default dtor
	*/
	~Texture();

	/**
	* Loads the data from the given xml node
	* @param node The xml node containing information about this texture
	*/
	void LoadFromNode(rapidxml::xml_node<char>* node);

	/**
	* Returns the string id of the texture
	* so we can find its location in a shader
	* @return char* id of the texture 
	*/
	inline char* GetID(){ return _id; }

	/**
	* Returns the gl reference texture
	* @return The integer used to reference the texture in opengl
	*/
	inline uint32 GetTextureID(){ return _texture; }

};

#endif