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
	glClearColor(r, g, b, a);
}

void VRenderer::ClearColorBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void VRenderer::ClearDepthBuffer()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void VRenderer::ClearAllBuffers()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}