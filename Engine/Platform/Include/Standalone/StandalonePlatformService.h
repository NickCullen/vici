#pragma once

#include "IPlatformService.h"

namespace Platform
{
	class StandalonePlatformService : IPlatformService
	{
	private:
		StandalonePlatformService();

	protected:
		virtual bool Load();
		virtual bool Unload();
	};
}