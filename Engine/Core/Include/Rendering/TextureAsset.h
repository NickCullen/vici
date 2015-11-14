#ifndef V_TEXTURE_ASSET
#define V_TEXTURE_ASSET

#include "CoreAPI.h"
#include "Asset.h"

/**
* TextureAsset is responsible for loading and unloading
* texture assets for scenes. Will also generate the OpenGL 
* TextureID
*/

class CORE_API TextureAsset : public Asset
{
	ASSET_REGISTER_DEF(TextureAsset)
private:
	int32 _width; /**< Width of the texture */
	int32 _height; /**< Height of the texture */
	int32 _comp; /**< Number of components the texture has i.e. grey = 1, greyalpha = 2, rgb = 3, rgba = 4 */

	uint32 _texture; /**< Texture reference in opengl */

	uint32 _type; /**< Type of texture (GL_TEXTURE_2D, GL_TEXTURE_3D etc. etc.) */

	/**
	* Returns the format in enum type given the
	* specified format string (from xml)
	* @param format The string format of the image can be one of the following - "grey, greyalpha, rgb, rgba"
	* @return integer reference the stb enum of the format
	*/
	uint32 GetFormat(char* format);

	/**
	* Returns the type of texture from the given strin
	* it should be the value of the 'type' node from
	* xml file
	* @param type The string containing the type of texture (1d, 2d, 3d etc.)
	* @return Unsigned integer containing the GL_TEXTURE_*D value
	*/
	uint32 GetType(char* type);
public:
	/**
	* Default constructor
	*/
	TextureAsset();

	/**
	* Default destructor
	*/
	~TextureAsset();

	/**
	* Loads the texture from the asset node
	* @param node The asset node
	*/
	virtual void Load(XmlNode& node);

	/**
	* Unload the texture from memory
	*/
	virtual void Unload();

	/**
	* Returns the gl reference texture
	* @return The integer used to reference the texture in opengl
	*/
	inline uint32 GetTextureID(){ return _texture; }

	/**
	* Binds the texture
	*/
	void Bind();

	
};








#endif