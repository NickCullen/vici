#include "Input.h"
#include "Display.h"

Input::Input() : Singleton<Input>()
{

}

Input::~Input()
{

}

bool Input::KeyDown(uint32 key)
{
	//glfwSetInputMode(_Display->GetRenderContext(), GLFW_STICKY_KEYS, 1);
	//return glfwGetKey(_Display->GetRenderContext(), key) == GLFW_PRESS;
	THROW_NOT_IMPL
	return false;
}

bool Input::KeyUp(uint32 key)
{
	//return glfwGetKey(_Display->GetRenderContext(), key) == GLFW_RELEASE;
	THROW_NOT_IMPL
	return false;
}

bool Input::Key(uint32 key)
{
	//int state = glfwGetKey(_Display->GetRenderContext(), key);
	//return state == GLFW_PRESS || state == GLFW_REPEAT;
	THROW_NOT_IMPL
	return false;
}

glm::vec2 Input::MousePosition()
{
	THROW_NOT_IMPL
	//get the windw coordinates
	double x = 0.0, y = 0.0;
	//glfwGetCursorPos(_Display->GetRenderContext(), &x, &y);

	//invert y!
	return glm::vec2(x,_Display->Height() - y);
}