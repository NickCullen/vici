#pragma once

#include "CoreAPI.h"
#include "VTypes.h"
#include "RendererTypes.h"

// Forward Decl.
struct VShaderHandle;
struct VShaderInputHandle;		// all shader inputs... Shader uniforms / samplers	/ per vertex data etc.
struct VShaderDebugFlags;

/* Constants */
#define _DECL_SHADER_INPUT(NAME, val) static const char* SHADER_IN_##NAME##_ID = #val;
#define _DECL_SHADER_UNIFORM(NAME, val) static const char* SHADER_UNIFORM_##NAME##_ID = #val;
#define _DECL_SHADER_OUTPUT(NAME, val) static const char* SHADER_OUT_##NAME##_ID = #val;

// Inputs
_DECL_SHADER_INPUT(POSITION, vPosition)
_DECL_SHADER_INPUT(COLOR, vColor)
_DECL_SHADER_INPUT(NORMAL, vNormal)
_DECL_SHADER_INPUT(TANGENT, vTangent)
_DECL_SHADER_INPUT(BINORMAL, vBinormal)
_DECL_SHADER_INPUT(UV1, vUV1)
_DECL_SHADER_INPUT(UV2, vUV2)
_DECL_SHADER_INPUT(UV3, vUV3)
_DECL_SHADER_INPUT(UV4, vUV4)

// Uniforms
_DECL_SHADER_UNIFORM(MODELVIEWPROJECTION, uModelViewProjectionMatrix)
_DECL_SHADER_UNIFORM(MODELVIEW, uModelViewMatrix)
_DECL_SHADER_UNIFORM(MODEL_MATRIX, uModelMatrix)
_DECL_SHADER_UNIFORM(NORMAL_MATRIX, uNormalMatrix)
_DECL_SHADER_UNIFORM(TIME, uTime)
_DECL_SHADER_UNIFORM(SCENE_AMBIENT, uSceneAmbient)

// Outputs
_DECL_SHADER_OUTPUT(COLOR, oColor)

/* Macro for unrolling common shader uniform + attribute locations */
#define _COMMON_SHADER_LOCATIONS(_GEN_) \
	_GEN_(ModelViewProjectionMatrix, SHADER_UNIFORM_MODELVIEWPROJECTION_ID, UniformLocation) \
	_GEN_(ModelViewMatrix, SHADER_UNIFORM_MODELVIEW_ID, UniformLocation) \
	_GEN_(ModelMatrix, SHADER_UNIFORM_MODEL_MATRIX_ID, UniformLocation) \
	_GEN_(NormalMatrix, SHADER_UNIFORM_NORMAL_MATRIX_ID, UniformLocation) \
	_GEN_(Time, SHADER_UNIFORM_TIME_ID, UniformLocation) \
	_GEN_(SceneAmbient, SHADER_UNIFORM_SCENE_AMBIENT_ID, UniformLocation) \
	_GEN_(Position, SHADER_IN_POSITION_ID, AttributeLocation) \
	_GEN_(VertexColor, SHADER_IN_COLOR_ID, AttributeLocation) \
	_GEN_(UV1, SHADER_IN_UV1_ID, AttributeLocation) \
	_GEN_(UV2, SHADER_IN_UV2_ID, AttributeLocation) \
	_GEN_(UV3, SHADER_IN_UV3_ID, AttributeLocation) \
	_GEN_(UV4, SHADER_IN_UV4_ID, AttributeLocation) \
	_GEN_(Normal, SHADER_IN_NORMAL_ID, AttributeLocation) \
	_GEN_(Tangent, SHADER_IN_TANGENT_ID, AttributeLocation) \
	_GEN_(Binormal, SHADER_IN_BINORMAL_ID, AttributeLocation)


/* Sets all locations to intial -1 */
#define _GEN_DEFAULT_VAL(variable, a ,b) variable##Location = nullptr;

/* Unrolls the input to generate member variables */
#define _GEN_MEMBERS(name, a, b) VShaderInputHandle* name##Location;

/* Unrolls the input to generate getters */
#define _GEN_GETTERS(name, a, b) inline VShaderInputHandle* Get##name##Location(){return name##Location;}

/* Unrolls the input to get the location */
#define _GEN_LOCATIONS(name, id, function) name##Location = function(id);

/**
* Class used to load shader files and store
* locations of commonly uniforms/attribues etc.
*/

class CORE_API VShader
{

private:
	class VFilePath* VPath; /**< path for vertex shader */
	class VFilePath* FPath; /**< Path for fragment shader */

	VShaderHandle* ShaderHandle;	/**< Underlying shader handle */

	bool Loaded; /**< Flag to show if the shader has been loaded */

	//the common shader code
	static char* CommonCode;

	//Generate members
	_COMMON_SHADER_LOCATIONS(_GEN_MEMBERS)

public:
	/**
	* Default ctor
	*/
	VShader();

	/**
	* Default dtor
	*/
	~VShader();

	void Unload();

	bool Load(const class VFilePath& vertexShaderPath, const class VFilePath& fragShaderPath);

	/** 
	* Use the shader
	*/
	void Use();

	/**
	* Returns the location of the specified sample
	* @param id The samplers name in the glsl shader
	*/
	VShaderInputHandle* SamplerLocation(const char* id);

	/**
	* Returns the location of the specified uniform
	* @param id The uniform id
	* @return Integer specifying the location of the uniform 
	*/
	VShaderInputHandle* UniformLocation(const char* id);

	/**
	* Returns the location of the specified attribute location
	* @param id of the attribute
	* @return integer specifiying the location of the attribute
	*/
	VShaderInputHandle* AttributeLocation(const char* id);

	/**
	* Binds the given out variable to the given location
	* @param id The name of the out variable in frag shader
	* @param location The location to bind the output
	*/
	void BindFragDataLocation(const char* id, uint32 location);

	/**
	* Check if shader is loaded or not
	* @return Returns true if loaded false if not
	*/
	inline bool IsLoaded(){ return Loaded; }

	/**
	* Debugs the shader
	* @param shaderProgram The shader to debug
	* @param checkType the type of check to carry out on the shader
	*/
	void DebugShader(const VShaderHandle& shaderProgram, unsigned int checkType);

	/**
	* Unlike debug shader this debugs the program as a whole
	* and checks for linking issues etc.
	* @param program The program to debug
	* @param checkType the type of check to carry out on the shader
	*/
	void DebugProgram(const VShaderHandle& program, unsigned int checkType);

	/**
	* Loads the shader common shader code into memory 
	*/
	static void LoadSharedCode(const char* cwd);

	/**
	* Unloads the shader common code from memory
	*/
	static void UnloadSharedCode();

	/* Create the member functions for getting locations */
	_COMMON_SHADER_LOCATIONS(_GEN_GETTERS)
};
