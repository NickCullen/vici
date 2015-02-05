#include "Material.h"


Material::Material()
{
	_hash = "Material";
}

Material::~Material()
{

}

void Material::Init(XmlNode& node)
{
	//get the shader
	char* shader = node.GetChild("shader").ValueString();
	_shader = (ShaderAsset*)_Assets->GetAsset(shader);

	//load textures
	XmlNode cur_texture = node.GetChild("texture");
	while (!cur_texture.IsNull())
	{
		//get the texture
		TextureAsset* texture = (TextureAsset*)_Assets->GetAsset(cur_texture.ValueString());

		//create a texture reference
		TextureReference ref;

		//set pointer to texture
		ref._tex = texture;

		//get the sampler uniform location
		char* uniform_name = cur_texture.GetAttributeString("uniform");
		ref._location = _shader->SamplerLocation(uniform_name);

		//add the texture reference to the list
		_textures.PushBack(ref);

		//get next texture
		cur_texture = cur_texture.NextSibling("texture");
	}
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
