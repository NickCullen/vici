#ifndef V_SHADER_ASSET
#define V_SHADER_ASSET

#include "Asset.h"
#include "CoreAPI.h"

/* Macro for unrolling common shader uniform + attribute locations */
#define _COMMON_SHADER_LOCATIONS(_GEN_) \
	_GEN_(mvp, "uModelViewProjectionMatrix", GetUniformLocationFunc) \
	_GEN_(mv, "uModelViewMatrix", GetUniformLocationFunc) \
	_GEN_(model_matrix, "uModelMatrix", GetUniformLocationFunc) \
	_GEN_(normal_matrix, "uNormalMatrix", GetUniformLocationFunc) \
	_GEN_(time, "uTime", GetUniformLocationFunc) \
	_GEN_(scene_ambience, "uSceneAmbience", GetUniformLocationFunc) \
	_GEN_(vertex, "aVertex", GetAttribLocationFunc) \
	_GEN_(uv, "aUV", GetAttribLocationFunc) \
	_GEN_(normal, "aNormal", GetAttribLocationFunc) \
	_GEN_(tangent, "aTangent", GetAttribLocationFunc) \
	_GEN_(binormal, "aBinormal", GetAttribLocationFunc)

/* Sets all locations to intial -1 */
#define _GEN_DEFAULT_VAL(variable, a ,b) _##variable##_loc = -1;

/* Unrolls the input to generate member variables */
#define _GEN_MEMBERS(name, a, b) UniformHandle _##name##_loc;

/* Unrolls the input to generate getters */
#define _GEN_GETTERS(name, a, b) inline UniformHandle name##Location(){return _##name##_loc;}

/* Unrolls the input to get the location */
#define _GEN_LOCATIONS(name, id, function) _##name##_loc = function(_program, id);

/**
* Class used to load shader files and store
* locations of commonly uniforms/attribues etc.
*/

class CORE_API ShaderAsset : public Asset
{
	ASSET_REGISTER_DEF(ShaderAsset)
private:
	char _v_path[256]; /**< path for vertex shader */
	char _f_path[256]; /**< Path for fragment shader */

	ShaderHandle _v; /**< The vertex shader */
	ShaderHandle _f; /**< The fragment shader */

	ShaderHandle _program; /**< The program as a whole */

	bool _is_loaded; /**< Flag to show if the shader has been loaded */

	//the common shader code
	static char* _common_code;

	//Generate members
	_COMMON_SHADER_LOCATIONS(_GEN_MEMBERS)

public:
	/**
	* Default ctor
	*/
	ShaderAsset();

	/**
	* Default dtor
	*/
	~ShaderAsset();

	/**
	* Load the shader from Asset node
	* @param node The asset node
	*/
	void Load(XmlNode& node);

	/**
	* Unloads the shader from memory
	*/
	void Unload();

	/**
	* Inline function returning the
	* shader program
	* @return uint32 representing the shader program internally
	*/
	inline ShaderHandle	Program(){ return _program; }

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
	* Check if shader is loaded or not
	* @return Returns true if loaded false if not
	*/
	inline bool IsLoaded(){ return _is_loaded; }

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
	static void LoadSharedCode(std::string cwd);

	/**
	* Unloads the shader common code from memory
	*/
	static void UnloadSharedCode();

	/* Create the member functions for getting locations */
	_COMMON_SHADER_LOCATIONS(_GEN_GETTERS)
};

#endif