#pragma once

#include "Singleton.h"

/**
 * Interface base class for all services
 */
namespace Core
{
	class IService
	{
	protected:
		bool bIsLoaded = false;		/**< Is this service loaded? */

		
		virtual bool Load() = 0;
		virtual bool Unload() = 0;
	public:
		bool IsLoaded() { return bIsLoaded; }
	};

	
}
