#pragma once

#include "PIL/PILAPI.h"
#include "PIL/DataTypes/PlatformTypes.h"


// Non public-abi definitions
struct VRenderContext;

// Forward decl.
class VShader;


// Typedefs


// Macros
#define CHECK_RENDERER_ERR VRenderer::CheckErrors()

/**
 * Class containing all required render functions and wraps
 * the underlying rendering system
 */
class PIL_API VRenderer
{
private:
	static VRenderer* Instance;

	static VRenderContext* CurrentContext;
public:
	VRenderer();
	~VRenderer();

	/**
	 * Returns the singelton instance
	 */
	static VRenderer* GetInstance();

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


	static void GetVersionString(const char** str);
	static void GetVersionNumber(int32* major, int32* minor);
	static void CheckErrors(const char* message = nullptr);

	void ClearColor(float32 r, float32 g, float32 b, float32 a = 1.0f);
	void ClearDepthBuffer();
	void ClearColorBuffer();
	void ClearAllBuffers();

	void SetViewport(int32 x, int32 y, int32 width, int32 height);
};

