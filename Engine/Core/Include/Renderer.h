#pragma once

#include "CoreAPI.h"
#include "Singleton.h"
#include "VTypes.h"
#include "RendererTypes.h"

class VShader;
struct VRenderContext;

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

	VShader* ActiveShader;	// The currently active shader

public:
	VRenderer();
	~VRenderer();

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

	static void GetVersionString(const char** str);
	static void GetVersionNumber(int32* major, int32* minor);
	static void CheckErrors(const char* message = nullptr);

	void ClearColor(float32 r, float32 g, float32 b, float32 a = 1.0f);
	void ClearDepthBuffer();
	void ClearColorBuffer();
	void ClearAllBuffers();

	void SetViewport(int32 x, int32 y, int32 width, int32 height);
	

	// VRenderer Setters
	inline void SetActiveShader(VShader* Shader) { ActiveShader = Shader; }
	

	
	inline VShader* GetActiveShader() { return ActiveShader; }
};
