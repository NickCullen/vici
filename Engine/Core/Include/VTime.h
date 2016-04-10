#pragma once

#include "CoreAPI.h"
#include "Singleton.h"

class CORE_API VTime : public VSingleton<VTime>
{
	friend class VSingleton<VTime>;

private:
	float Time;
	float DeltaTime;
	float FixedDeltaTime;

	VTime();
	~VTime() = default;
public:

	// Setters
	inline void UpdateTime();	// Will set Time using the native timer
	inline void SetDeltaTime(float dt) { DeltaTime = dt; }
	inline void SetFixedDeltaTime(float fdt) { FixedDeltaTime = fdt; }

	// Getters
	inline float GetTime() { return Time; }
	inline float GetDeltaTime() { return DeltaTime; }
	inline float GetFixedDeltaTime() { return FixedDeltaTime; }
};
