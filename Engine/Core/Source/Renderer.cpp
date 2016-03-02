#include "Renderer.h"
#include "GL/glew.h"
#include <stdio.h>

VRenderer::VRenderer() 
	:VSingleton(this)
{

}

VRenderer::~VRenderer()
{

}

bool VRenderer::Init()
{
	
	return true;
}

void VRenderer::GetVersionString(const char** str)
{
	*str = (const char*)glGetString(GL_VERSION);
}

void VRenderer::GetVersionNumber(int* major, int* minor)
{
	glGetIntegerv(GL_MAJOR_VERSION, major);
	glGetIntegerv(GL_MINOR_VERSION, minor);
}

void VRenderer::ClearColor(float r, float g, float b, float a)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(r, g, b, a);
}