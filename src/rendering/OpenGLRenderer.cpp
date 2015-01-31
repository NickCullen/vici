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
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	//set clear color
	glClearColor(col->r, col->g, col->b, col->a);

	//render flags
	glClear(flags);
}

void OpenGLRenderer::SetUniforms(Shader* shader)
{
	//set MVP matrix
	glUniformMatrix4fv(shader->MVPLocation(), 1, GL_FALSE, glm::value_ptr<float>(_ms._projection_matrix * _ms._view_matrix * _ms._current_matrix->_current_transform));

	//set normal matrix
	glm::mat3 normal_matrix = glm::inverseTranspose(glm::mat3(_ms._current_matrix->_current_transform));
	glUniformMatrix3fv(shader->NormalMatrixLocation(), 1, GL_FALSE, glm::value_ptr<float>(normal_matrix));
}