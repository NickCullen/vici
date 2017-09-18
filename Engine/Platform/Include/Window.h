#pragma once

#include "PlatformAPI.h"
#include "CoreIncludes.h"


namespace Platform
{
	class PLATFORM_API VWindow
	{
	private:
		struct SWindowNativePtr* WindowNativePtr = nullptr;	/**< Pointer to the underlying window system */

		int32 Width;
		int32 Height;
	public:
		
	public:

		~VWindow();

		bool Open(int32 x, int32 y, uint32 w, uint32 h);

		void Close();

		void PollEvents();

	};
}
