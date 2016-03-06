#pragma once

#include "CoreAPI.h"
#include "LinkedList.h"
#include "VString.h"
#include "VTypes.h"

class VShader;
class VTexture;

class CORE_API VMaterial
{
	struct VTextureParam
	{
		VString Name;	// Name in shader
		VTexture* Texture;	
		uint32	UniformLocation;	// location in shader
	};
private:
	VShader* Shader;		// Shader used to render this material

	VLinkedList<VTextureParam> Textures;	// Textures used in this material
public:
	VMaterial();

	~VMaterial();

	// Uses the shader and passes in its arguments
	void PrepareForRender();

	// Adds a texture parameter
	void AddTexture(const VString& name, VTexture* texture);

	// Setters
	void SetShader(VShader* shader);

	// Getters
	inline VShader* GetShader() { return Shader; }
};