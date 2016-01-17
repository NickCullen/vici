#include "AssetRegistrar.h"
#include "AssetFactory.h"


//#define _ASSETS_(_MOD_) \

//function to register asset with AssetFactory
#define _MOD_REG_ASSETS(Type) Type::Register();



void RegisterAssets()
{
	// Register with AssetFactory
	//_ASSETS_(_MOD_REG_ASSETS)
}


