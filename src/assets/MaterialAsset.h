#ifndef V_MATERIAL_ASSET
#define V_MATERIAL_ASSET
//
///* Forward Decl */
//class TextureAsset;
//
///* Includes */
//#include "Asset.h"
//#include "TList.h"
//
//#include "Shader.h"
///**
//* Structure to keep the id and texture
//* together so we can send it to the shader
//*/
//struct TextureReference
//{
//	TextureAsset* _tex; /**< The texture */
//	int32 _location; /**< The location of the texture sampler in the shader*/
//
//	/**
//	* Default constructor
//	*/
//	TextureReference()
//	{
//		_tex = NULL;
//		_location = -1;
//	}
//};
//
//class MaterialAsset : public Asset
//{
//private:
//	Shader _shader; /**< The shader used to render this material */
//
//	TList<TextureReference> _textures; /**< List of texture references so we can send them to the shader later */
//
//public:
//	MaterialAsset();
//
//	~MaterialAsset();
//
//	/**
//	* Loads the MaterialAsset from the asset node
//	* @param node The asset node
//	*/
//	virtual void Load(XmlNode& node);
//
//	/**
//	* Unload the MaterialAsset from memory
//	*/
//	virtual void Unload();
//
//	static AssetRegister<MaterialAsset> reg; /**< Static register for this asset type*/
//};
//
//
//





#endif