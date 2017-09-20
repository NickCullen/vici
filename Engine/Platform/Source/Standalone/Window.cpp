#include "Window.h"
#include "SDL.h"

using namespace Platform;

static bool SDLInitialized = false;

/**
 * Not exposes public - holds SDL window
 */
namespace Platform
{
	struct SWindowNativePtr
	{
		SDL_Window* SDLWindow;
	};
}


VWindow::~VWindow()
{
	Close();
	if (WindowNativePtr)
		delete(WindowNativePtr);
}

bool VWindow::Open(int32 x, int32 y, uint32 w, uint32 h)
{
	if (!SDLInitialized)
	{
		SDL_Init(SDL_INIT_VIDEO);
		SDLInitialized = true;
	}

	Close();		// Ensure it is closed first (i.e. native ptr is null)

	WindowNativePtr = new SWindowNativePtr;
	
	WindowNativePtr->SDLWindow = SDL_CreateWindow("Window", x, y, w, h, 0);
	if (WindowNativePtr->SDLWindow == nullptr)
	{
		delete(WindowNativePtr);
		WindowNativePtr = nullptr;

		return false;
	}

	bIsOpen = true;
	
	return true;
}

void VWindow::Close()
{
	if (WindowNativePtr != nullptr)
	{
		if (WindowNativePtr->SDLWindow != nullptr)
		{
			SDL_DestroyWindow(WindowNativePtr->SDLWindow);
			WindowNativePtr->SDLWindow = nullptr;
		}

		delete(WindowNativePtr);
		WindowNativePtr = nullptr;
	}
	
	bIsOpen = false;
}

void VWindow::PollEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) == SDL_TRUE)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			Close();
			return;
			break;
		
		default:
			break;
		}
	}
}
