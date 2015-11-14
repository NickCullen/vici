#include "AssetRegistrar.h"
#include "AssetFactory.h"
#include "ShaderAsset.h"
#include "MaterialAsset.h"
#include "MeshAsset.h"
#include "TextureAsset.h"

#define _ASSETS_(_MOD_) \
	_MOD_(ShaderAsset) \
	_MOD_(MaterialAsset) \
	_MOD_(MeshAsset) \
	_MOD_(TextureAsset)

//function to register asset with AssetFactory
#define _MOD_REG_ASSETS(Type) Type::Register();



void RegisterAssets()
{
	// Register with AssetFactory
	_ASSETS_(_MOD_REG_ASSETS)
}


