#include "Camera.h"
#include "Platform.h"
#include "OpenGLRenderer.h"
#include "Vici.h"

VCamera::VCamera()
{
	//default
	_clear_flags = 0;
	_clear_color = glm::vec4(0.2f,0.2f,0.2f, 1.0f);

	//get a scene renderer
	_renderer = new OpenGLRenderer();

	//initialize the scene
	_renderer->Init(this);

	//add to vici camera list
	Vici::_instance->_cameras.PushBack(this);
}
VCamera::~VCamera()
{
	//remove from vici camera list
	_vici->_cameras.Remove(this);

	//delete renderer
	delete (_renderer);
}

void VCamera::Init(GameObject* go, rapidxml::xml_node<char>* node)
{
	//remmeber to call parents init func
	IDrawable::Init(go, node);

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

//set up before rendinger
void VCamera::PrepareScene()
{
	//clear appropriate buffers
	_renderer->ClearBuffer(_clear_flags, &_clear_color);

	//set up projection matrices
	_projection_mat = glm::perspective<float>(45.0f, Display::AspectRatio(), 0.1f, 100.0f);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);


}

void VCamera::Render()
{
	for (unsigned int i = 0; i < _render_list.size(); i++)
	{
		_render_list[i]->PreRender(_renderer);
		_render_list[i]->Render(_renderer);
		_render_list[i]->PostRender(_renderer);
	}
}

void VCamera::AddGameObject(GameObject* go)
{
	_render_list.push_back(go);
}
void VCamera::RemoveGameObject(GameObject* go)
{
	//remove object here
}