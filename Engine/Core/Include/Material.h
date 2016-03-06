#pragma once

#include "CoreAPI.h"

class VShader;

class CORE_API VMaterial
{
private:
	VShader* Shader;		// Shader used to render this material


public:
	VMaterial();

	~VMaterial();

	// Uses the shader and passes in its arguments
	void PrepareForRender();

	// Setters
	inline void SetShader(VShader* shader) { Shader = shader; }

	// Getters
	inline VShader* GetShader() { return Shader; }
};