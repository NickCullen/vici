#pragma once

#include "PlatformAPI.h"
#include "CoreIncludes.h"


namespace Platform
{
	class PLATFORM_API VWindow
	{
	private:
		struct SWindowNativePtr* WindowNativePtr = nullptr;	/**< Pointer to the underlying window system */

		int32 Width = -1;
		int32 Height = -1;

		bool bIsOpen = false;

	public:
		
	public:

		~VWindow();

		bool Open(int32 x, int32 y, uint32 w, uint32 h);

		void Close();

		void PollEvents();

		inline int32 GetWidth() { return Width; }
		inline int32 GetHeight() { return Height; }
		inline bool IsOpen() { return bIsOpen; }
	};
}
