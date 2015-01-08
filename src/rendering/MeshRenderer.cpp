#include "MeshRenderer.h"
#include "Camera.h"

MeshRenderer::MeshRenderer()
{

}
MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::Init(GameObject* go, rapidxml::xml_node<char>* node)
{
	IDrawable::Init(go, node);

	
	//list for on enable and disable
	RegisterCallback(EComponentCallback::OnEnable);
	RegisterCallback(EComponentCallback::OnDisable);

	//render callbacks
	RegisterCallback(EComponentCallback::PreRender);
	RegisterCallback(EComponentCallback::OnRender);
	RegisterCallback(EComponentCallback::PostRender);
}

//required logic functions
void MeshRenderer::OnEnable()
{
	/*make sure camera will render this object*/
	VCamera* cam = LayerSystem::GetCameraForLayer(_go->GetLayer());
	if (cam)
		cam->AddGameObject(_go);
}
void MeshRenderer::OnDisable()
{
	/*make sure camera will not render this object*/
	VCamera* cam = LayerSystem::GetCameraForLayer(_go->GetLayer());
	if (cam)
		cam->RemoveGameObject(_go);
}

void MeshRenderer::PreRender(OpenGLRenderer* renderer)
{

}
void MeshRenderer::OnRender(OpenGLRenderer* renderer)
{
	glColor3f(0, 1, 0);
	glBegin(GL_POLYGON);
		glVertex3f(0.25, 0.25, 0.0);
		glVertex3f(0.75, 0.25, 0.0);
		glVertex3f(0.75, 0.75, 0.0);
		glVertex3f(0.25, 0.75, 0.0);
	glEnd();
}
void MeshRenderer::PostRender(OpenGLRenderer* renderer)
{


}