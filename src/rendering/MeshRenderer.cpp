#include "MeshRenderer.h"
#include "Camera.h"
#include "Material.h"
#include "Mesh.h"

MeshRenderer::MeshRenderer()
{
	//Important to set the hash if for this component
	_hash = "MeshRenderer";
	
	_material = NULL; 
	_mesh = NULL; 
	_shader = NULL; 
}
MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::Init(XmlNode& node)
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
	RegisterCallback(eUpdate, DELEGATE(MeshRenderer, Update, this));

	//get references
	_material = _go->FindComponent<Material>("Material");
	_mesh = _go->FindComponent<Mesh>("Mesh");
	
	//set shader
	if (_material)
	{
		_shader = _material->GetShader();

		//let the mesh create buffers
		//_mesh->CreateBuffers(_shader);
	}

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
	//use shader
	glUseProgram(_shader->Program());

	//set uniforms
	renderer->SetUniforms(_shader);

	//set material uniforms
	_material->SetUniforms();

	//send vertices to shader
	_mesh->SetArrays(_shader);

	//draw
	_mesh->DrawElements();
}
void MeshRenderer::PostRender(OpenGLRenderer* renderer)
{


}

//for testing
void MeshRenderer::Update()
{
	static float rot = 0;

	rot++;

	//rotate
	_transform->Rotate(glm::radians(rot), glm::vec3(0, 1, 0));



}