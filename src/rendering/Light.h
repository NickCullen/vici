#ifndef V_LIGHT
#define V_LIGHT

#include "IComponent.h"

/**
* Class containing information for lights 
* In the scene. 
*/

class Light : public IComponent
{
private:

public:
	/**
	* Default constructor
	*/
	Light();

	/**
	* Default destructor
	*/
	~Light();

	/**
	* Used to initilize light from node
	* @param node Node containing component data
	*/
	virtual void Init(XmlNode& node);

	/**
	* Registers to callbacks 
	*/
	virtual void OnStart();

	/**
	* Called when the light becomes enabled
	*/
	void OnEnabled();

	/**
	* Called when the light becomes disabled
	*/
	void OnDisabled();


	/**
	* Sets this light at the appropriate
	* location of the shader
	* @param shader The shader that we are using
	* @param index The index into the light array in the glsl shader
	*/
	void SetUniform(ShaderAsset* shader, int32 index);

	/**
	* Checks if the attenuation of this light will reach
	* the transform position. If so it will return true.
	* @param transform Transform pointer to the position to check
	* @return Boolean signalling if it reached or not
	bool InRange(Transform* transform);

	static DerivedRegister<Light> reg; /**< Used to register this class with ComponetFactory */

};

#endif