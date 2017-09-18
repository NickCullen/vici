#pragma once

#include "PlatformAPI.h"
#include "CoreTypes.h"

class PLATFORM_API Window
{
private:

public:

	static Window* Open(int32 x, int32 y, uint32 w, uint32 h);
};