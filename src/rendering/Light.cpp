#include "Light.h"
#include "Camera.h"
#include "OpenGLRenderer.h"

Light::Light() : IComponent()
{
	_attenuation = 5.0f;
	_type = eDirectional;
	_intensity = glm::vec4(1.0f,0.0f,0.0f,1.0f);
}

Light::~Light()
{

}

void Light::Init(XmlNode& node)
{
	//call parents Init
	IComponent::Init(node);

	//get nodes
	XmlNode intensity_node = node.GetChild("intensity");
	
	//set values
	if(!intensity_node.IsNull())
		sscanf(intensity_node.ValueString(), "%f %f %f %f", &_intensity[0], &_intensity[1], &_intensity[2], &_intensity[3]);

}

void Light::OnStart()
{
	//register to enabled and disabled
	RegisterCallback(eOnEnable, DELEGATE(Light, OnEnabled, this));
	RegisterCallback(eOnDisable, DELEGATE(Light, OnDisabled, this));
	RegisterCallback(eUpdate, DELEGATE(Light, Update, this));
}

void Light::SetUniform(ShaderAsset* shader, int32 index)
{
	//buffer it up
	char buff [64];
	sprintf(buff, "%s[%d]", "uLights", index);

	//convert to std::string for easier string manipulation
	std::string uniform = buff;

	//type (0 = directional 1 = spot 2 = cone)
	int32 loc = shader->UniformLocation((uniform + ".type").c_str());
	if(loc != -1) glUniform1i(loc, (int)_type);

	//attenuation
	loc = shader->UniformLocation((uniform + ".attenuation").c_str());
	if(loc != -1) glUniform1f(loc, _attenuation);

	//position
	loc = shader->UniformLocation((uniform + ".position").c_str());
	if(loc != -1) glUniform4fv(loc, 1, glm::value_ptr<float>(_transform->GetPosition()));

	//direction
	loc = shader->UniformLocation((uniform + ".direction").c_str());
	if(loc != -1) glUniform4fv(loc, 1, glm::value_ptr<float>(_transform->ForwardDirection()));

	//intensity
	loc = shader->UniformLocation((uniform + ".intensity").c_str());
	if(loc != -1) glUniform4fv(loc,1,glm::value_ptr<float>(_intensity));

	//Platform_LogString("%f %f %f\n", _transform->ForwardDirection().x,_transform->ForwardDirection().y,_transform->ForwardDirection().z);
}

bool Light::InRange(Transform* transform)
{
	return _type != eDirectional ? (glm::distance(_transform->GetPosition(), transform->GetPosition()) <= _attenuation) : true;
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
void Light::Update()
{
	static float rot = 0.0f;

	_transform->Rotate(glm::radians(rot++), glm::vec3(0, 1, 0));
}

