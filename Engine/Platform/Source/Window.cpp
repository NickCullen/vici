#include "Window.h"
#include "SDL.h"

static bool SDLInitialized = false;

Window* Window::Open(int32 x, int32 y, uint32 w, uint32 h)
{
	Window* ret = new Window();

	if (!SDLInitialized)
	{
		SDL_Init(SDL_INIT_VIDEO);
		SDLInitialized = true;
	}

	SDL_CreateWindow("Window", x, y, w, h, NULL);
	return ret;
}