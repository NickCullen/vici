#ifndef V_LIGHT
#define V_LIGHT

#include "IComponent.h"

/**
* Enum specifying the type of the light
* 0 = directional 
* 1 = point
* 2 = spot
*/
enum LightType
{
	eDirectional = 0,
	ePoint = 1,
	eSpot = 2,
};

/**
* Class containing information for lights 
* In the scene. 
*/

class Light : public IComponent
{
private:
	LightType _type;	/**< The type of light */

	float _constant_attenuation; 	/**< constant attenuation */
	float _linear_attenuation;		/**< Linear attenuation */
	float _quadratic_attenuation;	/**< Quadratic attenuation */

	glm::vec4 _ambient;		/**< Ambient intensity of the light */
	glm::vec4 _diffuse;		/**< Diffuse intensity of the light */
	glm::vec4 _specular;	/**< Specular intensity of the light */

	float _range;			/**< The distance this light will reach */
	
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
	* @return Boolean specifying if the light will effect the object at position or not
	*/
	bool InRange(Transform* transform);

	static ComponentRegister<Light> reg; /**< Used to register this class with ComponetFactory */

	/**
	* Testing 
	*/
	void Update();
};


#endif