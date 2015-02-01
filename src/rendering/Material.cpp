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

	//load textures
	rapidxml::xml_node<char>* cur_texture = node->first_node("texture");
	while (cur_texture != NULL)
	{
		//instantiate a texture
		Texture* tex = new Texture();

		//Load the texture
		tex->LoadFromNode(cur_texture);

		//create a texture reference
		TextureReference ref;

		//set pointer to texture
		ref._tex = tex;

		//get the sampler uniform location
		char* uniform_name = cur_texture->first_attribute("id")->value();
		ref._location = _shader.SamplerLocation(uniform_name);

		//add the texture reference to the list
		_textures.PushBack(ref);

		//get next texture
		cur_texture = cur_texture->next_sibling("texture");
	}
}


void Material::SetShader(char* vert, char* frag)
{
	if (vert == NULL || frag == NULL) return;

	_shader.Create(vert, frag);
}

void Material::SetUniforms()
{
	int count = 0;

	TLIST_foreach(TextureReference, tex, _textures)
	{
		//set the texture this sampler will use
		glUniform1i((*tex)._location, count); 

		//bind the texture to that active texture location
		glActiveTexture(GL_TEXTURE0 + count);
		
		//bind it
		(*tex)._tex->Bind();

		count ++;
		
	}
}
