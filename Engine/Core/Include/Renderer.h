#pragma once

#include "CoreAPI.h"
#include "Singleton.h"

class CORE_API VRenderer : public VSingleton<VRenderer>
{
private:

public:
	VRenderer();
	~VRenderer();

	static bool Init();
	static void GetVersionString(const char** str);
	static void GetVersionNumber(int* major, int* minor);

	void ClearColor(float r, float g, float b, float a = 1.0f);
	void ClearDepthBuffer();
	void ClearColorBuffer();
	void ClearAllBuffers();

};