#include "Light.h"
#include "Camera.h"
#include "OpenGLRenderer.h"

Light::Light() : IComponent()
{

}

Light::~Light()
{

}

void Light::Init(XmlNode& node)
{
	//call parents Init
	IComponent::Init(node);


}

void Light::OnStart()
{
	//register to enabled and disabled
	RegisterCallback(eOnEnable, DELEGATE(Light, OnEnabled, this));
	RegisterCallback(eOnDisable, DELEGATE(Light, OnDisabled, this));
}

void Light::SetUniform(Shader* shader, int32 index)
{
	
}

void Light::OnEnabled()
{
	//add this light to the relevant camera
	VCamera* cam = LayerSystem::GetCameraForLayer(_go->GetLayer());
	if (cam)
		cam->GetRenderer()->AddLight(this);
}

void Light::OnDisabled()
{
	//remove this light from the relevant camera
	VCamera* cam = LayerSystem::GetCameraForLayer(_go->GetLayer());
	if (cam)
		cam->GetRenderer()->RemoveLight(this);
}