#include "PIL/Graphics/Material.h"
#include "PIL/Graphics/OpenGL/Include/Glew.h"
#include "PIL/Graphics/Texture.h"

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

	for (auto item = Uniforms.GetFirst(); item; item = Uniforms.GetNext(item))
	{
		ParamHandle* cur = &item->Data;
		if (cur->Handle >= 0)
		{
			cur->Param->SendToShader(cur->Handle);
		}
	}
}

void VMaterial::CleanupAfterRender()
{
	for (auto item = Uniforms.GetFirst(); item; item = Uniforms.GetNext(item))
	{
		ParamHandle* cur = &item->Data;
		if (cur->Handle >= 0)
		{
			cur->Param->CleanupFromShader();
		}
	}
}

void VMaterial::AddParam(const VString& name, IMaterialParam* param)
{
	ParamHandle prm;
	
	if(Shader)
		prm.Handle = Shader->UniformLocation(name.c_str());

	prm.Param = param;
	prm.Name = name;

	Uniforms.Add(prm);
}

void VMaterial::SetShader(VShader* shader)
{
	Shader = shader;
	if (Shader)
	{
		// Cache texture locations
		for (auto item = Uniforms.GetFirst(); item; item = Uniforms.GetNext(item))
		{
			ParamHandle* cur = &item->Data;
			cur->Handle = Shader->UniformLocation(cur->Name.c_str());
		}
	}
}