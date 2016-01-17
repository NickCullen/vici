#include "ComponentRegistrar.h"
#include "ComponentFactory.h"


//#define _COMPONENTS_(_MOD_) 

//function to register asset with AssetFactory
#define _MOD_REG_COMPONENT_(Type) Type::Register();

void RegisterComponents()
{
	//_COMPONENTS_(_MOD_REG_COMPONENT_)
}