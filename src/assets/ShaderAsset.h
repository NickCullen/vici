#ifndef V_SHADER_ASSET
#define V_SHADER_ASSET

#include "Asset.h"

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

	GLint _mvp_loc; /**< Location of mvp matrix uniform location */
	GLint _mv_loc;	/**< Location of the model view matrix location */
	GLint _model_matrix_loc;	/**< Location of the model matrix location */
	GLint _normal_matrix_loc; /**< Location of normal matrix uniform location */
	GLint _time_location; /**< Location of the time uniform in the shader */
	GLint _scene_ambience_location; /**< Location of the scene ambience location*/

	GLint _vertex_location; /**< Location of vertex in attribute */
	GLint _uv_location; /**< Location of uv in attribute */
	GLint _normal_location; /**< Location of normal in attribute */
	GLint _tangent_location; /**< Location of tangent in attribute */
	GLint _binormal_location; /**< Location of binormal in attribute */

	bool _is_loaded; /**< Flag to show if the shader has been loaded */
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
	* Returns the model-view-projection matrix location
	* @return int
	*/
	inline GLint MVPLocation(){ return _mvp_loc; }

	/**
	* Returns the model-view-projection matrix location
	* @return int
	*/
	inline GLint MVLocation(){ return _mv_loc; }

	/**
	* Returns the model matrix location
	* @return int
	*/
	inline GLint ModelMatrixLocation(){ return _model_matrix_loc; }
	
	/**
	* Returns the normal matrix location
	* @return int
	*/
	inline GLint NormalMatrixLocation(void){ return _normal_matrix_loc; }

	/**
	* Returns the in vertex attribute location
	* @return int
	*/
	inline GLint VertexLocation(){ return _vertex_location; }

	/**
	* Returns the int uv attribute location
	* @return int
	*/
	inline GLint UVLocation(){ return _uv_location; }

	/**
	* Returns the in normal attribute location
	* @return int
	*/
	inline GLint NormalLocation(){ return _normal_location; }

	/**
	* Returns the in normal attribute location
	* @return int
	*/
	inline GLint BinormalLocation(){ return _binormal_location; }

	/**
	* Returns the in normal attribute location
	* @return int
	*/
	inline GLint TangentLocation(){ return _tangent_location; }

	/**
	* Returns the location of the time uniform
	* @return int containing the uniformlocation for the time variable
	*/
	inline GLint TimeLocation(){ return _time_location; }

	/**
	* Returns the location of the scene ambience uniform
	* @return int containing the uniform location
	*/
	inline GLint SceneAmbienceLocation(){ return _scene_ambience_location; }

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

	static AssetRegister<ShaderAsset> reg; /**< Used to register the asset to the asset factory */
};

#endif