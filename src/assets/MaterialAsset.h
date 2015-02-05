#ifndef V_MATERIAL_ASSET
#define V_MATERIAL_ASSET

/* Forward Decl */
class TextureAsset;

/* Includes */
#include "Asset.h"
#include "glm.h"

class MaterialAsset : public Asset
{
	friend class Material;
private:
	glm::vec4 _ka;	/**< Material Ambience */
	glm::vec4 _kd;	/**< Material Diffuse */
	glm::vec4 _ks;	/**< Material Spec */
	float _ns;	/**< Material Shininess */
	float _d;	/**< Material dissolve */
	int32 _illum;	/**< Illumination Model */


	std::string _map_amb;	/**< Material ambient map (asset id)*/
	std::string _map_diff;	/**< Material Diffuse Map (asset id)*/
	std::string _map_spec;	/**< Material Specular Map (asset id)*/

	std::string _map_bump;	/**< Material Bump Map (asset id)*/
public:
	MaterialAsset();

	~MaterialAsset();

	/**
	* Loads the MaterialAsset from the asset node
	* @param node The asset node
	*/
	virtual void Load(XmlNode& node);

	/**
	* Unload the MaterialAsset from memory
	*/
	virtual void Unload();

	static AssetRegister<MaterialAsset> reg; /**< Static register for this asset type*/
};








#endif