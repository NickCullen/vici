#pragma once

#include "CoreAPI.h"
#include "Singleton.h"
#include "VTypes.h"

class CORE_API VRenderer : public VSingleton<VRenderer>
{
private:
	uint32 ContextID;	// The id of the current context  (0 is default)

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
	void SetContextID(uint32 id);

	inline uint32 GetContextID() { return ContextID; }
};