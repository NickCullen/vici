#include "MeshRenderer.h"
#include "Camera.h"

MeshRenderer::MeshRenderer()
{
	//Important to set the hash if for this component
	_hash = "MeshRenderer";

}
MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::Init(rapidxml::xml_node<char>* node)
{
	//call parent init
	IDrawable::Init(node);
}

//implementation of SetupCallbacks
void MeshRenderer::OnStart()
{
	//list for on enable and disable
	RegisterCallback(eOnEnable, DELEGATE(MeshRenderer, OnEnable, this));
	RegisterCallback(eOnDisable, DELEGATE(MeshRenderer, OnDisable, this));
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