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
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("Failed to init glew\n");
		return false;
	}
	return true;
}

void VRenderer::ClearColor(float r, float g, float b, float a)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(r, g, b, a);
}