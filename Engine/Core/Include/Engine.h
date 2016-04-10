#pragma once

#include "CoreAPI.h"
#include "Singleton.h"
#include "EngineIncludes.h"

class CORE_API VEngine : public VSingleton<VEngine>
{
private:
	uint32 CurrentFrame;			// Frame counter

public:
	VEngine();
	~VEngine();

	bool Init(int argc, const char** argv);

	void FixedUpdate();
	void Update();
	void Render();

	// Setters
	inline void SetCurrentFrame(uint32 val) { CurrentFrame = val; }

	// Getters
	inline uint32 GetCurrentFrame() { return CurrentFrame; }
};
