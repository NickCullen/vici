#include "OpenGLRenderer.h"
#include "Camera.h"


OpenGLRenderer::OpenGLRenderer()
{
	_cam = NULL;
}

OpenGLRenderer::~OpenGLRenderer()
{

}

/*if this is override please remember to call base.Init()*/
void OpenGLRenderer::Init(VCamera* cam)
{
	_cam = cam;
}

/*Pre scene initialization*/
void OpenGLRenderer::PreSceneRender()
{
	
}

/*During scene renering */
void OpenGLRenderer::RenderScene()
{

}

/* post scene rendering */
void OpenGLRenderer::PostSceneRender()
{

}

void OpenGLRenderer::ClearBuffer(int flags, glm::vec4* col)
{
	//set clear color
	glClearColor(col->r, col->g, col->b, col->a);

	//render flags
	glClear(flags);
}