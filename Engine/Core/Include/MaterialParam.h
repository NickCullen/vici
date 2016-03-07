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
	virtual bool SendToShader(UniformHandle handle) = 0;
};