#pragma once

#include "CoreAPI.h"
#include "Singleton.h"
#include "VTypes.h"
#include "RendererTypes.h"


// Non public-abi forward decl.
struct VRenderContext;
struct VShaderHandle;
struct VShaderInputHandle;
struct VShaderDebugFlags;

// Typedefs


// Macros
#define CHECK_RENDERER_ERR VRenderer::CheckErrors()

/**
 * Class containing all required render functions and wraps
 * the underlying rendering system
 */
class CORE_API VRenderer : public VSingleton<VRenderer>
{
private:
	static VRenderContext* CurrentContext;

	VShaderHandle* ActiveShader;	// The currently active shader

public:
	VRenderer();
	~VRenderer();

#pragma region - Render Contexts -

	/**
	 * Creates a render context
	 */
	VRenderContext* CreateContext();

	/**
	 * Sets the specified context to current
	 */
	void SetCurrentContext(VRenderContext* context);

	/**
	 * Returns the current context
	 */
	inline VRenderContext* GetCurrentContext() { return CurrentContext; }

	/**
	 * Returns the integer id of the current context
	 */
	uint32 GetContextID();

	/**
	 * Destroys the given context
	 */
	void DestroyContext(VRenderContext* context);

#pragma endregion

#pragma region - Shaders -

	/**
	* Creates a shader handles (vertex/geom/fragment)
	* note this does not create the shader yet
	*/
	VShaderHandle* CreateShaderHandles(int EShaderMask);

	/**
	 * Sets the source of the shader
	 */
	void SetShaderSource(VShaderHandle* handle, EShaderType type, char** source);

	/**
	 * Compile the specified shader, this will link them all up
	 */
	void CompileShader(VShaderHandle* handle);

	/**
	 * Destroys the given shader handle
	 */
	void DestroyShader(VShaderHandle* shader);

	/**
	 * Sets the shader to be active and use it
	 * @return returns true if successfully used
	 */
	bool SetActiveShader(VShaderHandle* handle);

	/**
	 * Binds the frag shaders output to the given location 
	 * @param shaderHandle the handle to the shader object
	 * @param id The id of the output
	 * @param the location of the output
	 */
	void BindFragDataLocation(VShaderHandle* shaderHandle, const char* id, uint32 location);

	/**
	 * Returns the uniform location in the shader
	 * @param shader The handle to the shader object
	 * @param uniformName The name of the uniform you want to retrieve
	 * @return Returns the UniformHandle object pointer (nullptr if it doesn't exist)
	 */
	VShaderInputHandle* GetUniformHandle(VShaderHandle* shader, const char* uniformName);

	/**
	* Returns the sampler location in the shader
	* @param shader The handle to the shader object
	* @param samplerName The name of the sampler you want to retrieve
	* @return Returns the UniformHandler object pointer (nullptr if it doesn't exist)
	*/
	VShaderInputHandle* GetSamplerHandle(VShaderHandle* shader, const char* samplerName);

	/**
	* Returns the attribute location in the shader
	* @param shader The handle to the shader object
	* @param attribName The name of the attribute (vertex data) you want to retrieve
	* @return Returns the VAttributeHandle object pointer (nullptr if it doesn't exist)
	*/
	VShaderInputHandle* GetAttributeHandle(VShaderHandle* shader, const char* attribName);

#pragma endregion

#pragma region - Vertex manipulation -
	/**
	 * Enables the array of vertex data
	 * @param attributeArrayHandle The handle to the vertex array handle
	 */
	void EnableVertexAttribArray(VShaderInputHandle* attributeArrayHandle);

	/**
	 * Sets the info of the vertex array
	 * @param atrribArrayHandle The handle to the vertex array 
	 * @param vertexElement The element of the vertex which contains its info
	 * @param vertexSize size per vertex
	 */
	void VertexAttribPointer(VShaderInputHandle* attribArrayHandle, const struct VVertexElement* vertexElement, int32 vertexSize);
#pragma endregion


#pragma region - Uniform & Texture manipulation -

	/**
	 * Binds a uniform to the given location
	 * @param handle The uniform handle in the shader
	 * @param uniform The integer id of the binding uniform
	 */

	void BindUniform(VShaderInputHandle* handle, int32 uniform);

#pragma endregion

	static void GetVersionString(const char** str);
	static void GetVersionNumber(int32* major, int32* minor);
	static void CheckErrors(const char* message = nullptr);

	void ClearColor(float32 r, float32 g, float32 b, float32 a = 1.0f);
	void ClearDepthBuffer();
	void ClearColorBuffer();
	void ClearAllBuffers();

	void SetViewport(int32 x, int32 y, int32 width, int32 height);
};
