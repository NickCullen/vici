#pragma once

#include "PIL/PILAPI.h"

/**
 * Interface class for passing paramters to shader
 * Any data type which can be passed in as a uniform to a shader
 * should inherit from this
 */
class PIL_API IMaterialParam
{
protected:
public:
	/**
	 * Default ctor
	 */
	IMaterialParam();

	/**
	 * Default dtor
	 */
	~IMaterialParam();

	/**
	 * Pure virtual method, override to do logic for passing into the shader
	 * @param handle The handle to this argument in the shader
	 * @return Returns true if succesfully sent to shader
	 */
	virtual bool SendToShader(struct VShaderInputHandle* handle) = 0;

	/**
	 * Chance to cleanup after render
	 */
	virtual void CleanupFromShader() = 0;
};