#include "Input.h"
#include "Display.h"

bool Input::KeyDown(uint32 key)
{
	glfwSetInputMode(Display::Window(), GLFW_STICKY_KEYS, 1);
	return glfwGetKey(Display::Window(), key) == GLFW_PRESS;
}

bool Input::KeyUp(uint32 key)
{
	return glfwGetKey(Display::Window(), key) == GLFW_RELEASE;
}

bool Input::Key(uint32 key)
{
	int state = glfwGetKey(Display::Window(), key);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

glm::vec2 Input::MousePosition()
{
	//get the windw coordinates
	double x = 0.0, y = 0.0;
	glfwGetCursorPos(Display::Window(), &x, &y);

	//invert y!
	return glm::vec2(x,Display::Height() - y);
}