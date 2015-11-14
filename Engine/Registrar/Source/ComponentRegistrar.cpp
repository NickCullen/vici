#include "ComponentRegistrar.h"
#include "ComponentFactory.h"
#include "Camera.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "Light.h"

#define _COMPONENTS_(_MOD_) \
	_MOD_(Camera) \
	_MOD_(Material) \
	_MOD_(MeshRenderer) \
	_MOD_(Light) 

//function to register asset with AssetFactory
#define _MOD_REG_COMPONENT_(Type) Type::Register();

void RegisterComponents()
{
	_COMPONENTS_(_MOD_REG_COMPONENT_)
}