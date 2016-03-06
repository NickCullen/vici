#include "Material.h"
#include "Shader.h"
#include "Glew.h"
#include "Texture.h"

VMaterial::VMaterial()
	:Shader(nullptr)
{

}

VMaterial::~VMaterial()
{

}

void VMaterial::PrepareForRender()
{
	Shader->Use();

	int loc = 0;
	for (auto item = Textures.GetFirst(); item; item = Textures.GetNext(item), loc++)
	{
		VTextureParam* cur = &item->Data;
		if (cur->UniformLocation >= 0)
		{
			item->Data.Texture->Bind(loc);
			glUniform1i(item->Data.UniformLocation, loc);
		}
	}
}

void VMaterial::AddTexture(const VString& name, VTexture* texture)
{
	VTextureParam prm;

	prm.Name = name;
	prm.Texture = texture;

	if(Shader)
		prm.UniformLocation = Shader->UniformLocation(prm.Name.c_str());

	Textures.Add(prm);
}

void VMaterial::SetShader(VShader* shader)
{
	Shader = shader;
	if (Shader)
	{
		// Cache texture locations
		for (auto item = Textures.GetFirst(); item; item = Textures.GetNext(item))
		{
			VTextureParam* cur = &item->Data;
			cur->UniformLocation = Shader->UniformLocation(cur->Name.c_str());
		}
	}
}