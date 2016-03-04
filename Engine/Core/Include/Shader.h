#pragma once

#include "CoreAPI.h"
#include "VTypes.h"

/* Macro for unrolling common shader uniform + attribute locations */
#define _COMMON_SHADER_LOCATIONS(_GEN_) \
	_GEN_(ModelViewProjectionMatrix, "uModelViewProjectionMatrix", UniformLocation) \
	_GEN_(ModelViewMatrix, "uModelViewMatrix", UniformLocation) \
	_GEN_(ModelMatrix, "uModelMatrix", UniformLocation) \
	_GEN_(NormalMatrix, "uNormalMatrix", UniformLocation) \
	_GEN_(Time, "uTime", UniformLocation) \
	_GEN_(SceneAmbient, "uSceneAmbient", UniformLocation) \
	_GEN_(Position, "aPosition", AttributeLocation) \
	_GEN_(UV, "aUV", AttributeLocation) \
	_GEN_(Normal, "aNormal", AttributeLocation) \
	_GEN_(Tangent, "aTangent", AttributeLocation) \
	_GEN_(Binormal, "aBinormal", AttributeLocation)

/* Typedefs */
typedef int32 ShaderHandle;
typedef int32 UniformHandle;
typedef int32 SamplerHandle;
typedef uint32 ShaderDebugFlags;

/* Constants */
static const char* SHADER_COLOUR_OUT_ID = "outColor";

/* Sets all locations to intial -1 */
#define _GEN_DEFAULT_VAL(variable, a ,b) variable##Location = -1;

/* Unrolls the input to generate member variables */
#define _GEN_MEMBERS(name, a, b) UniformHandle name##Location;

/* Unrolls the input to generate getters */
#define _GEN_GETTERS(name, a, b) inline UniformHandle Get##name##Location(){return name##Location;}

/* Unrolls the input to get the location */
#define _GEN_LOCATIONS(name, id, function) name##Location = function(id);

/**
* Class used to load shader files and store
* locations of commonly uniforms/attribues etc.
*/

class CORE_API VShader
{

private:
	char* VPath; /**< path for vertex shader */
	char* FPath; /**< Path for fragment shader */

	ShaderHandle VHandle; /**< The vertex shader */
	ShaderHandle FHandle; /**< The fragment shader */

	ShaderHandle Program; /**< The program as a whole */

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

	bool Load(const char* vertexShaderPath, const char* fragShaderPath);

	/** 
	* Use the shader
	*/
	void Use();

	/**
	* Inline function returning the
	* shader program
	* @return uint32 representing the shader program internally
	*/
	inline ShaderHandle	GetProgram(){ return Program; }

	/**
	* Returns the location of the specified sample
	* @param id The samplers name in the glsl shader
	*/
	SamplerHandle SamplerLocation(const char* id);

	/**
	* Returns the location of the specified uniform
	* @param id The uniform id
	* @return Integer specifying the location of the uniform 
	*/
	UniformHandle UniformLocation(const char* id);

	/**
	* Returns the location of the specified attribute location
	* @param id of the attribute
	* @return integer specifiying the location of the attribute
	*/
	UniformHandle AttributeLocation(const char* id);

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
	void DebugShader(ShaderHandle shaderProgram, ShaderDebugFlags checkType);

	/**
	* Unlike debug shader this debugs the program as a whole
	* and checks for linking issues etc.
	* @param program The program to debug
	* @param checkType the type of check to carry out on the shader
	*/
	void DebugProgram(ShaderHandle program, ShaderDebugFlags checkType);

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
