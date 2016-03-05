#pragma once

#include "CoreAPI.h"
#include "Singleton.h"
#include "EngineConstants.h"
#include "EngineMacros.h"

class CORE_API VEngine : public VSingleton<VEngine>
{
private:

public:
	VEngine();
	~VEngine();

	bool Init(int argc, const char** argv);

	void Render();
};