#include "Time.h"
#include "GLFW/glfw3.h"

float VTime::GetTime()
{
	return (float)glfwGetTime();
}