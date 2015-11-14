#ifndef V_MATERIAL
#define V_MATERIAL

#include "IComponent.h"
#include "CoreAPI.h"
#include "SmartPtr.h"
#include "TextureAsset.h"
#include "ShaderAsset.h"
#include "MaterialAsset.h"

/**
* Structure to keep the id and texture
* together so we can send it to the shader
*/
struct CORE_API TextureReference
{
	AssetPointer<TextureAsset> _tex; /**< The texture */
	SamplerHandle _sampler_location; /**< The location of the texture sampler in the shader*/

	/**
	* Default constructor
	*/
	TextureReference()
	{
		_sampler_location = -1;
	}
};

/** 
* Material class containing a reference to the shader
* that will render this material and a list of textures
* to be sent to the shader. Will also get the location
* of the material properties in the shader
*/

class CORE_API Material : public IComponent
{
	COMPONENT_REGISTER_DEF(Material)

private:
	AssetPointer<ShaderAsset> _shader; /**< The shader used to render this material */

	TList<TextureReference> _textures; /**< List of texture references so we can send them to the shader later */

	AssetPointer<MaterialAsset> _material_asset; /**< The asset file containing default material properties */


	UniformHandle _material_ka_location; /**< Location of material ambience */
	UniformHandle _material_kd_location; /**< Location of material diffuse */
	UniformHandle _material_ks_location; /**< Location of material specular */
	UniformHandle _material_ns_location; /**< Location of material shininess */
	UniformHandle _material_d_location;	 /**< Location of material dissolve */
	UniformHandle _material_illum_location; /**< Location of material illumination model location */

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
	virtual void Init(XmlNode& node);


	/**
	* Returns a pointer to the shader used to render
	* this material
	* @return Pointer to shader (note can be NULL if shader isnt loaded)
	*/
	inline AssetPointer<ShaderAsset> GetShader()
	{
		return _shader ? _shader->IsLoaded() ? _shader : AssetPointer<ShaderAsset>(NULL) : AssetPointer<ShaderAsset>(NULL);
	}

	/**
	* Sets all the required uniforms in the shader 
	* such uniforms include textures, material properties etc.
	*/
	void SetUniforms();

};

#endif