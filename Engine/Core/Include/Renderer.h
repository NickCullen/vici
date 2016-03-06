#pragma once

#include "CoreAPI.h"
#include "Singleton.h"
#include "VTypes.h"

class VShader;

// Macros
#define CHECK_RENDERER_ERR VRenderer::CheckErrors()

class CORE_API VRenderer : public VSingleton<VRenderer>
{
private:
	uint32 ContextID;	// The id of the current context  (0 is default)

	VShader* ActiveShader;	// The currently active shader

public:
	VRenderer();
	~VRenderer();

	static bool Init();
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
	inline void SetContextID(uint32 id) { ContextID = id; }

	// VRenderer Getters
	inline uint32 GetContextID() { return ContextID; }
	inline VShader* GetActiveShader() { return ActiveShader; }
};