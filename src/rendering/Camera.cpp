#include "Camera.h"
#include "Platform.h"
#include "OpenGLRenderer.h"
#include "Vici.h"

VCamera::VCamera()
{
	//Important to set the hash if for this component
	_hash = "VCamera";

	//default
	_clear_flags = 0;
	_clear_color = glm::vec4(0.2f,0.2f,0.2f, 1.0f);
}
VCamera::~VCamera()
{

}

void VCamera::Init(rapidxml::xml_node<char>* node)
{
	//remmeber to call parents init func
	IComponent::Init(node);

	//get and set the clear flags
	_clear_flags = atoi(node->first_node("clear_color_buffer")->value()) == 1? VICI_COLOR_BUFFER_BIT : 0;
	_clear_flags |= atoi(node->first_node("clear_depth_buffer")->value()) == 1 ? VICI_DEPTH_BUFFER_BIT : 0;
	_clear_flags |= atoi(node->first_node("clear_accum_buffer")->value()) == 1 ? VICI_ACCUM_BUFFER_BIT : 0;
	_clear_flags |= atoi(node->first_node("clear_stencil_buffer")->value()) == 1 ? VICI_STENCIL_BUFFER_BIT : 0;

	//setup all the layers this camera will render
	rapidxml::xml_node<char>* layer = node->first_node("renderlayers")->first_node();
	while (layer)
	{
		//get the render layer
		unsigned int render_layer = atoi(layer->value());

		//set it up
		LayerSystem::SetCameraForLayer(this, render_layer);

		layer = layer->next_sibling();
	}

}

void VCamera::OnStart()
{
	//add to vici camera list
	_vici->_cameras.PushBack(this);

	//get a scene renderer
	_renderer = new OpenGLRenderer();

	//initialize the scene
	_renderer->Init(this);
}

void VCamera::OnDestroy()
{
	//remove from vici camera list
	_vici->_cameras.Remove(this);

	//delete renderer
	delete (_renderer);

	//call parents on destroy
	IComponent::OnDestroy();
}
//set up before rendinger
void VCamera::PrepareScene()
{
	//clear appropriate buffers
	_renderer->ClearBuffer(_clear_flags, &_clear_color);

	//load matrix identity   
	_renderer->_ms.Identity();

	//set up projection matrices
	_projection_mat = glm::perspective<float>(45.0f, Display::AspectRatio(), 0.1f, 100.0f);

	//_view_mat = glm::translate(_view_mat, glm::vec3(0, 0, 10));

	_view_mat = glm::lookAt(_transform->GetPosition(), // Camera is at (4,3,3), in World Space
							glm::vec3(0, 0, 0), // and looks at the origin
							glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
							);


	//specify the view and projection matrices
	_renderer->_ms.SetProjection(_projection_mat);
	_renderer->_ms.SetView(_view_mat);
}

void VCamera::Render()
{
	TLIST_foreach(GameObject*, obj, _render_list)
	{
		//push a matrix
		_renderer->_ms.PushMatrix();

		//apply model matrix
		_renderer->_ms.ApplyMatrix(obj->GetTransform()->GetModelMatrix());

		//set the MVP matrices in the matrix stack
		obj->PreRender(_renderer);
		obj->Render(_renderer);
		obj->PostRender(_renderer);

		//pop if off the stack
		_renderer->_ms.PopMatrix();
	}
}

void VCamera::AddGameObject(GameObject* go)
{
	_render_list.PushBack(go);
}
void VCamera::RemoveGameObject(GameObject* go)
{
	_render_list.Remove(go);
}