#include "Renderer.h"
#include "Glew.h"
#include <stdio.h>

VRenderer::VRenderer() 
	:VSingleton(this),
	ContextID(0)
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

void VRenderer::GetVersionNumber(int32* major, int32* minor)
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

void VRenderer::ClearColor(float32 r, float32 g, float32 b, float32 a)
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

void VRenderer::SetViewport(int32 x, int32 y, int32 width, int32 height)
{
	glViewport(x, y, width, height);
}

void VRenderer::SetContextID(uint32 id)
{
	ContextID = id;
}