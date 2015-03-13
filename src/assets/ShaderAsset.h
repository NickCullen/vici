#ifndef V_SHADER_ASSET
#define V_SHADER_ASSET

#include "Asset.h"

/* Macro for unrolling common shader uniform + attribute locations */
#define _COMMON_SHADER_LOCATIONS(_GEN_) \
	_GEN_(mvp, "uModelViewProjectionMatrix", glGetUniformLocation) \
	_GEN_(mv, "uModelViewMatrix", glGetUniformLocation) \
	_GEN_(model_matrix, "uModelMatrix", glGetUniformLocation) \
	_GEN_(normal_matrix, "uNormalMatrix", glGetUniformLocation) \
	_GEN_(time, "uTime", glGetUniformLocation) \
	_GEN_(scene_ambience, "uSceneAmbience", glGetUniformLocation) \
	_GEN_(vertex, "aVertex", glGetAttribLocation) \
	_GEN_(uv, "aUV", glGetAttribLocation) \
	_GEN_(normal, "aNormal", glGetAttribLocation) \
	_GEN_(tangent, "aTangent", glGetAttribLocation) \
	_GEN_(binormal, "aBinormal", glGetAttribLocation)
	

/* Sets all locations to intial -1 */
#define _GEN_DEFAULT_VAL(variable, a ,b) _##variable##_loc = -1;

/* Unrolls the input to generate member variables */
#define _GEN_MEMBERS(name, a, b) GLint _##name##_loc;

/* Unrolls the input to generate getters */
#define _GEN_GETTERS(name, a, b) inline GLint name##Location(){return _##name##_loc;}

/* Unrolls the input to get the location */
#define _GEN_LOCATIONS(name, id, function) _##name##_loc = function(_program, id);

/**
* Class used to load shader files and acess
* locations of uniforms/attribues etc.
* Status (new - ongoing)
*/

class ShaderAsset : public Asset
{
private:
	char _v_path[256]; /**< path for vertex shader */
	char _f_path[256]; /**< Path for fragment shader */

	GLuint _v; /**< The vertex shader */
	GLuint _f; /**< The fragment shader */

	GLuint _program; /**< The program as a whole */

	bool _is_loaded; /**< Flag to show if the shader has been loaded */

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
	inline GLuint	Program(){ return _program; }

	/**
	* Returns the location of the specified sample
	* @param id The samplers name in the glsl shader
	*/
	GLint SamplerLocation(const char* id);

	/**
	* Returns the location of the specified uniform
	* @param id The uniform id
	* @return Integer specifying the location of the uniform 
	*/
	GLint UniformLocation(const char* id);

	/**
	* Check if shader is loaded or not
	* @return Returns true if loaded false if not
	*/
	inline bool IsLoaded(){ return _is_loaded; }

	/**
	* Destroys the shader if it was created
	*/
	void Clean();

	/**
	* Creates the shader from the given vertex and fragment
	* shader paths, this is the file path with the extension
	* @param vertex_shader The path to the vertex shader with file extension
	* @param fragment_shader The path to the fragment shader with file extension
	*/
	void Create(char* vertex_shader, char* fragment_shader);

	/**
	* Debugs the shader
	* @param shaderProgram The shader to debug
	* @param checkType the type of check to carry out on the shader
	*/
	void DebugShader(GLuint shaderProgram, GLenum checkType);

	/**
	* Unlike debug shader this debugs the program as a whole
	* and checks for linking issues etc.
	* @param program The program to debug
	* @param checkType the type of check to carry out on the shader
	*/
	void DebugProgram(GLuint program, GLenum checkType);

	/* Create the member functions for getting locations */
	_COMMON_SHADER_LOCATIONS(_GEN_GETTERS)

	static AssetRegister<ShaderAsset> reg; /**< Used to register the asset to the asset factory */
};

#endif