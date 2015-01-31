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

void OpenGLRenderer::SetUniforms(Shader* shader)
{
	glUniformMatrix4fv(shader->MVPLocation(), 1, GL_FALSE, glm::value_ptr<float>(_ms._projection_matrix * _ms._view_matrix * _ms._current_matrix->_current_transform));
}