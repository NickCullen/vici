#include "Material.h"


Material::Material()
{
	_hash = "Material";
}

Material::~Material()
{

}

void Material::Init(rapidxml::xml_node<char>* node)
{
	//get the shader paths
	char* vert = node->first_node("vert")->value();
	char* frag = node->first_node("frag")->value();

	//load shader
	SetShader(vert, frag);
}


void Material::SetShader(char* vert, char* frag)
{
	if (vert == NULL || frag == NULL) return;

	_shader.Create(vert, frag);
}