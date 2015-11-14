#include "Material.h"
#include "AssetLoader.h"

Material::Material()
{
	_hash = "Material";

	//set defaults
	_material_ka_location = _material_kd_location = _material_ks_location = _material_ns_location = _material_d_location = _material_illum_location = -1;
}

Material::~Material()
{

}

void Material::Init(XmlNode& node)
{
	//get the shader
	char* shader = node.GetChild("shader").ValueString();
	_shader = _Assets->GetAsset<ShaderAsset>(shader);

	//get locations
	if (_shader)
	{
		_material_ka_location = _shader->UniformLocation("uMaterial.ka");
		_material_kd_location = _shader->UniformLocation("uMaterial.kd");
		_material_ks_location = _shader->UniformLocation("uMaterial.ks");
		_material_ns_location = _shader->UniformLocation("uMaterial.ns");
		_material_d_location = _shader->UniformLocation("uMaterial.d");
		_material_illum_location = _shader->UniformLocation("uMaterial.illum");
	}

	//load textures
	XmlNode cur_texture = node.GetChild("texture");
	while (!cur_texture.IsNull())
	{
		//get the texture
		AssetPointer<TextureAsset> texture = _Assets->GetAsset<TextureAsset>(cur_texture.ValueString());

		//create a texture reference
		TextureReference ref;

		//set pointer to texture
		ref._tex = texture;

		//get the sampler uniform location
		char* uniform_name = cur_texture.GetAttributeString("uniform");
		ref._sampler_location = _shader->SamplerLocation(uniform_name);

		//add the texture reference to the list
		_textures.PushBack(ref);

		//get next texture
		cur_texture = cur_texture.NextSibling("texture");
	}

	//Get the material asset if any
	XmlNode material_node = node.GetChild("material");
	if (!material_node.IsNull())
	{
		_material_asset = _Assets->GetAsset<MaterialAsset>(material_node.ValueString());
	}
}

void Material::SetUniforms()
{
	int count = 0;

	//set textures
	TLIST_foreach(TextureReference, tex, _textures)
	{
		//set the texture this sampler will use
		glUniform1i((*tex)._sampler_location, count); 

		//bind the texture to that active texture location
		glActiveTexture(GL_TEXTURE0 + count);
		
		//bind it
		(*tex)._tex->Bind();

		count ++;	
	}

	//set materials
	if (_material_asset)
	{
		if (_material_ka_location != -1) glUniform4fv(_material_ka_location, 1, glm::value_ptr<float>(_material_asset->_ka));
		if (_material_kd_location != -1) glUniform4fv(_material_kd_location, 1, glm::value_ptr<float>(_material_asset->_kd));
		if (_material_ks_location != -1) glUniform4fv(_material_ks_location, 1, glm::value_ptr<float>(_material_asset->_ks));
		if (_material_ns_location != -1) glUniform1f(_material_ns_location, _material_asset->_ns);
		if (_material_d_location != -1) glUniform1f(_material_d_location, _material_asset->_d);
		if (_material_illum_location != -1)  glUniform1i(_material_ka_location, _material_asset->_illum);
	}
}
