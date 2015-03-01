#include "Light.h"
#include "Camera.h"
#include "OpenGLRenderer.h"

Light::Light() : IComponent()
{
	_constant_attenuation = 1.0f;
	_linear_attenuation = 0.0014f;
	_quadratic_attenuation = 0.000007f;

	_type = eDirectional;
	_ambient = _diffuse = _specular = glm::vec4(1.0f,0.0f,0.0f,1.0f);

	_reach = 20.0f;
}

Light::~Light()
{

}

void Light::Init(XmlNode& node)
{
	//call parents Init
	IComponent::Init(node);

	//get nodes
	XmlNode ambient_node = node.GetChild("ambient");
	XmlNode diffuse_node = node.GetChild("diffuse");
	XmlNode specular_node = node.GetChild("specular");
	XmlNode type_node = node.GetChild("type");
	XmlNode constant_attenuation_node = node.GetChild("constant_attenuation");
	XmlNode linear_attenuation_node = node.GetChild("linear_attenuation");
	XmlNode quadratic_attenuation_node = node.GetChild("quadratic_attenuation");
	
	//set values
	if(!ambient_node.IsNull())
		sscanf(ambient_node.ValueString(), "%f %f %f %f", &_ambient[0], &_ambient[1], &_ambient[2], &_ambient[3]);
	if(!diffuse_node.IsNull())
		sscanf(diffuse_node.ValueString(), "%f %f %f %f", &_diffuse[0], &_diffuse[1], &_diffuse[2], &_diffuse[3]);
	if(!specular_node.IsNull())
		sscanf(specular_node.ValueString(), "%f %f %f %f", &_specular[0], &_specular[1], &_specular[2], &_specular[3]);
	if(!type_node.IsNull())
		_type = (LightType)type_node.ValueInt();
	if(!constant_attenuation_node.IsNull())
		_constant_attenuation = constant_attenuation_node.ValueFloat();
	if(!linear_attenuation_node.IsNull())
		_linear_attenuation = linear_attenuation_node.ValueFloat();
	if(!quadratic_attenuation_node.IsNull())
		_quadratic_attenuation = quadratic_attenuation_node.ValueFloat();
	
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

	// constant attenuation
	loc = shader->UniformLocation((uniform + ".constantAttenuation").c_str());
	if(loc != -1) glUniform1f(loc, _constant_attenuation);

	// linear attenuation
	loc = shader->UniformLocation((uniform + ".linearAttenuation").c_str());
	if(loc != -1) glUniform1f(loc, _linear_attenuation);

	// quadratic attenuation
	loc = shader->UniformLocation((uniform + ".quadraticAttenuation").c_str());
	if(loc != -1) glUniform1f(loc, _quadratic_attenuation);

	//position
	loc = shader->UniformLocation((uniform + ".position").c_str());
	if(loc != -1) glUniform4fv(loc, 1, glm::value_ptr<float>(_transform->GetPosition()));

	//direction
	loc = shader->UniformLocation((uniform + ".direction").c_str());
	if(loc != -1) glUniform4fv(loc, 1, glm::value_ptr<float>(_transform->ForwardDirection()));

	//ambient ntensity
	loc = shader->UniformLocation((uniform + ".ambient").c_str());
	if(loc != -1) glUniform4fv(loc,1,glm::value_ptr<float>(_ambient));

	//diffuse ntensity
	loc = shader->UniformLocation((uniform + ".diffuse").c_str());
	if(loc != -1) glUniform4fv(loc,1,glm::value_ptr<float>(_diffuse));

	//specular ntensity
	loc = shader->UniformLocation((uniform + ".specular").c_str());
	if(loc != -1) glUniform4fv(loc,1,glm::value_ptr<float>(_specular));

	//Platform_LogString("%f %f %f\n", _transform->ForwardDirection().x,_transform->ForwardDirection().y,_transform->ForwardDirection().z);
}


bool Light::InRange(Transform* transform)
{
	return _type != eDirectional ? (glm::distance(_transform->GetPosition(), transform->GetPosition()) <= _reach) : true;
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

	//Platform_LogString("Light forward = %f %f %f\n", _transform->ForwardDirection().x, _transform->ForwardDirection().y, _transform->ForwardDirection().z);
	_transform->Rotate(rot++, glm::vec3(0, 1, 0));
}
