#pragma once

#include "CoreAPI.h"

class CORE_API VTime
{
private:

public:
	VTime() = default;
	~VTime() = default;

	/**
	* Returns the time in seconds
	*/
	static float GetTime();
};