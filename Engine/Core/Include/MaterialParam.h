#pragma once

#include "CoreAPI.h"
#include "Shader.h"
/**
 * Interface class for passing paramters to shader
 */
class CORE_API IMaterialParam
{
protected:
public:
	IMaterialParam();
	~IMaterialParam();

	// Pass the data to the shader
	virtual bool SendToShader(struct VShaderInputHandle* handle) = 0;

	// Chance to cleanup after render
	virtual void CleanupFromShader() = 0;
};