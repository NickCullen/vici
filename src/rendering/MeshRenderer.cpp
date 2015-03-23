#include "MeshRenderer.h"
#include "Camera.h"
#include "Material.h"

MeshRenderer::MeshRenderer()
{
	//Important to set the hash if for this component
	_hash = "MeshRenderer";
	
	_material = NULL; 
	_indices = 0;
	_recieve_lighting = true;
}
MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::Init(XmlNode& node)
{
	//call parent init
	IDrawable::Init(node);

	//get the indices index
	_indices = node.GetInt("indices");

	//get the mesh asset
	_mesh = _Assets->GetAsset<MeshAsset>(node.GetString("mesh"));
}

//implementation of SetupCallbacks
void MeshRenderer::OnStart()
{
	//list for on enable and disable
	RegisterCallback(eOnEnable, DELEGATE(MeshRenderer, OnEnable, this));
	RegisterCallback(eOnDisable, DELEGATE(MeshRenderer, OnDisable, this));

	//get references
	_material = _go->FindComponent<Material>("Material");
}

//required logic functions
void MeshRenderer::OnEnable()
{
	/*make sure camera will render this object*/
	VCamera* cam = _Layers->GetCameraForLayer(_go->GetLayer());
	if (cam)
		cam->AddGameObject(_go);
}
void MeshRenderer::OnDisable()
{
	/*make sure camera will not render this object*/
	VCamera* cam = _Layers->GetCameraForLayer(_go->GetLayer());
	if (cam)
		cam->RemoveGameObject(_go);
}

void MeshRenderer::OnRender(OpenGLRenderer* renderer)
{
	//if no material - return!
	if(!_material) return;

	//dont try rendering with a null shader
	AssetPointer<ShaderAsset> shader = _material->GetShader();
	if(!shader) return;

	//use shader
	glUseProgram(shader->Program());

	//set uniforms
	renderer->SetUniforms(shader.get());

	//if recieving lighting - set uniforms
	if(_recieve_lighting) renderer->SetLightUniforms(shader.get(), _transform);

	//set material uniforms
	_material->SetUniforms();

	//send vertices to shader
	_mesh->SetArrays(shader.get());

	//draw
	_mesh->DrawElements(_indices);
}
