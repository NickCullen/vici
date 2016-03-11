#include "Time.h"
#include "GLFW/glfw3.h"

VTime::VTime()
	:VSingleton(this)
{

}
void VTime::UpdateTime()
{
	Time = (float)glfwGetTime();
}