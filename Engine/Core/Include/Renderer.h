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
	void ClearColor(float r, float g, float b, float a = 1.0f);
};