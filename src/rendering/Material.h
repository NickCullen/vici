#ifndef V_MATERIAL
#define V_MATERIAL

#include "IComponent.h"

/**
* Structure to keep the id and texture
* together so we can send it to the shader
*/
struct TextureReference
{
	Texture* _tex; /**< The texture */
	int32 _location; /**< The location of the texture sampler in the shader*/

	/**
	* Default constructor
	*/
	TextureReference()
	{
		_tex = NULL;
		_location = -1;
	}
};

/** 
* Material represents how a surface is made up
* status (new - ongoing)
*/

class Material : public IComponent
{
private:
	Shader _shader; /**< The shader used to render this material */

	TList<TextureReference> _textures; /**< List of texture references so we can send them to the shader later */

public:
	/** 
	* Default ctor
	*/
	Material();

	/**
	* Default dtor
	*/
	~Material();

	/**
	* Used to initilize material from node
	* @param node Node containing component data
	*/
	virtual void Init(rapidxml::xml_node<char>* node);


	/**
	* Returns a pointer to the shader used to render
	* this material
	* @return Pointer to shader (note can be NULL if shader isnt loaded)
	*/
	inline Shader* GetShader()
	{
		return _shader.IsLoaded() ? &_shader : NULL;
	}

	/**
	* Sets and loads the vertex and fragment shader for 
	* this material. Calling this function will trigger the 
	* process for loading and initializing the shader
	* @param vert File path with extension to vertex shader
	* @param frag File path with extension to fragment shader
	*/
	void SetShader(char* vert, char* frag);

	/**
	* Sets all the required uniforms in the shader 
	* such uniforms include textures, material properties etc.
	*/
	void SetUniforms();

	static DerivedRegister<Material> reg; /**< Used to register this class with ComponetFactory */
};

#endif