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
		//create
		Texture* tex = new Texture();

		// loaad
		tex->LoadFromNode(cur_texture);

		//add the texture to the list
		_textures.PushBack(tex);

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

	TLIST_foreach(Texture*, tex, _textures)
	{
		//get the textures location in the shader
		int32 location = _shader.SamplerLocation(tex->GetID());

		glUniform1i(location, count); //Texture unit 0 is for base images.

		//When rendering an objectwith this program.
		glActiveTexture(GL_TEXTURE0 + count);
		glBindTexture(GL_TEXTURE_2D, tex->GetTextureID());

		count ++;
		
	}
}
