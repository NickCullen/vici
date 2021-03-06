#pragma once

#include "Core/CoreAPI.h"
#include "PIL/Graphics/MaterialParam.h"
#include "PIL/Collections/LinkedList.h"
#include "PIl/DataTypes/PlatformTypes.h"
#include "PIL/Collections/String.h"

// Forward decl.
class VTexture;
class VShader;
struct VShaderInputHandle;

class CORE_API VMaterial
{
	/**
	 * couples the uniform location 
	 * and the data together
	 */
	struct ParamHandle
	{
		VShaderInputHandle* Handle;		// Uniform location of param in the shader
		IMaterialParam* Param;		// The param data
		VString Name;				// Name of the argument in the shader
	};

private:
	VShader* Shader;		// Shader used to render this material

	VLinkedList<ParamHandle> Uniforms;	// Uniforms to send to the shader
public:
	VMaterial();

	~VMaterial();

	// Uses the shader and passes in its arguments
	void PrepareForRender();

	// Cleanup after render (this is simple cleanup, no alloc/dealloc should be 
	// happening here - this should be done as fast as possible
	void CleanupAfterRender();

	// Adds a paramter to the shader
	void AddParam(const VString& name, IMaterialParam* param);

	// Setters
	void SetShader(VShader* shader);

	// Getters
	inline VShader* GetShader() { return Shader; }
};