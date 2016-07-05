#pragma once

#include "PIL/PILAPI.h"
#include "PIL/DataTypes/PlatformTypes.h"

// Non-public abi struct
struct VInternalTimeData;

class PIL_API VTime
{
private:
	static VTime* Instance;
	
	VInternalTimeData* InternalTime;

	double Time;
	double DeltaTime;
	double FixedDeltaTime;

	VTime();
	~VTime() = default;
public:
	static VTime* GetInstance()
	{
		if (Instance == nullptr)
			Instance = new VTime();
		return Instance;
	}

	// Setters
	inline void UpdateTime();	// Will set Time using the native timer
	inline void SetDeltaTime(float dt) { DeltaTime = dt; }
	inline void SetFixedDeltaTime(float fdt) { FixedDeltaTime = fdt; }

	// Getters
	inline double GetTime() { return Time; }
	inline double GetDeltaTime() { return DeltaTime; }
	inline double GetFixedDeltaTime() { return FixedDeltaTime; }
};

// Static init
VTime* VTime::Instance = nullptr;