#include "Input.h"
#include "Display.h"
#include "Vector2.h"

Input::Input() : Singleton<Input>()
{

}

Input::~Input()
{

}

bool Input::KeyDown(SDL_Keycode key)
{
	const uint8 *state = SDL_GetKeyboardState(NULL);
	return state[SDL_GetScancodeFromKey(key)];
}

bool Input::KeyUp(SDL_Keycode key)
{
	const uint8 *state = SDL_GetKeyboardState(NULL);
	return !(state[SDL_GetScancodeFromKey(key)]);
}

bool Input::Key(SDL_Keycode key)
{
	const uint8 *state = SDL_GetKeyboardState(NULL);
	return state[SDL_GetScancodeFromKey(key)];
}

Vector2f Input::MousePosition()
{
	static Vector2f v;
	SDL_GetMouseState((int*)&v.x, (int*)&v.y);
	return v;
}