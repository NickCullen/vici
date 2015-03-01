#include "Light.h"
#include "Camera.h"
#include "OpenGLRenderer.h"

Light::Light() : IComponent()
{
	_type = eDirectional;
	_ambient = _diffuse = _specular = glm::vec4(1.0f,0.0f,0.0f,1.0f);
	_range = 5.0f;

	//calculate attenuation from range
	_constant_attenuation = 1.0f;
	_linear_attenuation = 4.5f/_range;
	_quadratic_attenuation = 75.0f/(_range*_range);
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
	XmlNode range_node = node.GetChild("range");

	//set values
	if(!ambient_node.IsNull())
		sscanf(ambient_node.ValueString(), "%f %f %f %f", &_ambient[0], &_ambient[1], &_ambient[2], &_ambient[3]);
	if(!diffuse_node.IsNull())
		sscanf(diffuse_node.ValueString(), "%f %f %f %f", &_diffuse[0], &_diffuse[1], &_diffuse[2], &_diffuse[3]);
	if(!specular_node.IsNull())
		sscanf(specular_node.ValueString(), "%f %f %f %f", &_specular[0], &_specular[1], &_specular[2], &_specular[3]);
	if(!type_node.IsNull())
		_type = (LightType)type_node.ValueInt();
	if(!range_node.IsNull())
		_range = range_node.ValueFloat();

	_constant_attenuation = 1.0f;
	_linear_attenuation = 4.5f/_range;
	_quadratic_attenuation = 75.0f/(_range*_range);
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
	static float d = 0.0f;
	static float max_reach = 0.0f;

	switch(_type)
	{
		case eDirectional:
			return true;

		case ePoint:
			return glm::distance(_transform->GetPosition(), transform->GetPosition()) <= _range;

		case eSpot:
			return (glm::distance(_transform->GetPosition(), transform->GetPosition()) <= _range);

		default:
			return false;
	}

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

	
	//forward back
	if(Input::KeyDown(GLFW_KEY_O))
	{
		_transform->Translate(glm::vec3(0,0,-1) * 0.02f);
	}
	else if(Input::KeyDown(GLFW_KEY_L))
	{
		_transform->Translate(glm::vec3(0,0,1) * 0.02f);
	}


	//Platform_LogString("Light dir = %f %f %f\n", _transform->GetPosition().x, _transform->GetPosition().y, _transform->GetPosition().z);
	//_transform->Rotate(rot++, glm::vec3(0, 1, 0));
}
