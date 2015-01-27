#ifndef V_MATERIAL
#define V_MATERIAL

#include "IComponent.h"

/** 
* Material represents how a surface is made up
* status (new - ongoing)
*/

class Material : public IComponent
{
private:
	Shader _shader; /**< The shader used to render this material */

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

	static DerivedRegister<Material> reg; /**< Used to register this class with ComponetFactory */
};

#endif