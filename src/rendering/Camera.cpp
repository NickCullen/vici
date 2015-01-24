#include "Camera.h"
#include "Platform.h"
#include "OpenGLRenderer.h"
#include "Vici.h"

VCamera::VCamera()
{
	//default
	_clear_flags = 0;
	_clear_color = glm::vec4(0.2f,0.2f,0.2f, 1.0f);

	//add to vici camera list
	Vici::_instance->_cameras.PushBack(this);
}
VCamera::~VCamera()
{

}

void VCamera::Init(GameObject* go, rapidxml::xml_node<char>* node)
{
	//Important to set the hash if for this component
	_hash = "VCamera";

	//remmeber to call parents init func
	IComponent::Init(go, node);

	//get a scene renderer
	_renderer = new OpenGLRenderer();

	//initialize the scene
	_renderer->Init(this);


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

	RegisterCallback(eUpdate, DELEGATE(VCamera, Update, this));
}

void VCamera::Update()
{
	Destroy(_go);
}
void VCamera::OnDestroy()
{
	//remove from vici camera list
	_vici->_cameras.Remove(this);

	//delete renderer
	delete (_renderer);
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

	//specify the view and projection matrices
	_renderer->_ms.SetProjection(_projection_mat);
	_renderer->_ms.SetView(_view_mat);

	//OLD OPEN GL NOTE THIS WILL CHANGE 
	//I AM JUST WORKING ON LOGIC FUNCTIONS AT THE MOMENT
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

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