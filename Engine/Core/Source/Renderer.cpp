#include "Renderer.h"
#include "Glew.h"
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

void VRenderer::CheckErrors(const char* message)
{
	GLenum error = glGetError();
	while (error != GL_NO_ERROR)  // make sure we check all Error flags!
	{
		if (message != nullptr)
			printf("OpenGL ErrorID: %d\n\tUserMessage: %s\n", error, message);
		else
			printf("OpenGL ErrorID: %d\n", error);
		error = glGetError(); // get next error if any.
	}
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

void VRenderer::SetViewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
}