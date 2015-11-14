#include "Renderer.h"
#include "Camera.h"
#include "VTime.h"
#include "ShaderAsset.h"

Renderer::Renderer()
{
	_cam = NULL;
	_scene_ambience = glm::vec4(0.1f,0.1f,0.1f,1.0f);
}

Renderer::~Renderer()
{
}

/*if this is override please remember to call base.Init()*/
void Renderer::Init(VCamera* cam)
{
	_cam = cam;
}

/*Pre scene initialization*/
void Renderer::PreSceneRender()
{
	
}

/*During scene renering */
void Renderer::RenderScene()
{

}

/* post scene rendering */
void Renderer::PostSceneRender()
{

}



void Renderer::ClearBuffer(int flags, const glm::vec4& col)
{
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	//set clear color
	glClearColor(col.r, col.g, col.b, col.a);

	//render flags
	glClear(flags);
}

void Renderer::SetUniforms(ShaderAsset* shader)
{
	//set MVP and MV and model matrix
	glUniformMatrix4fv(shader->mvpLocation(), 1, GL_FALSE, glm::value_ptr<float>(_ms->_projection_matrix * _ms->_view_matrix * _ms->_current_matrix->_current_transform));
	glUniformMatrix4fv(shader->mvLocation(), 1, GL_FALSE, glm::value_ptr<float>(_ms->_view_matrix * _ms->_current_matrix->_current_transform));
	glUniformMatrix4fv(shader->model_matrixLocation(), 1, GL_FALSE, glm::value_ptr<float>(_ms->_current_matrix->_current_transform));

	//set normal matrix
	glm::mat3 normal_matrix = glm::inverseTranspose(glm::mat3(_ms->_current_matrix->_current_transform));
	glUniformMatrix3fv(shader->normal_matrixLocation(), 1, GL_FALSE, glm::value_ptr<float>(normal_matrix));

	//push globals
	glUniform1f(shader->timeLocation(), _Time->Time());
	glUniform4fv(shader->scene_ambienceLocation(), 1, glm::value_ptr<float>(_scene_ambience));
}
