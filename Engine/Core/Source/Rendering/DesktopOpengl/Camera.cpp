#include "Camera.h"
#include "Platform.h"
#include "Display.h"
#include "Renderer.h"
#include "Vici.h"
#include "MatrixStack.h"

Camera::Camera()
{
	//Important to set the hash if for this component
	_hash = "Camera";

	//default
	_clear_flags = 0;

	//lovely bit of consants! :D
	_clear_color = glm::vec4(0.36078431372549f,0.47843137254902f,1.0f, 1.0f);
}
Camera::~Camera()
{

}

void Camera::Init(XmlNode& node)
{
	//remmeber to call parents init func
	IComponent::Init(node);

	//get and set the clear flags
	_clear_flags = node.GetChild("clear_color_buffer").ValueBool() ? GL_COLOR_BUFFER_BIT : 0;
	_clear_flags |= node.GetChild("clear_depth_buffer").ValueBool() ? GL_DEPTH_BUFFER_BIT : 0;
	_clear_flags |= node.GetChild("clear_accum_buffer").ValueBool() ? GL_ACCUM_BUFFER_BIT : 0;
	_clear_flags |= node.GetChild("clear_stencil_buffer").ValueBool() ? GL_STENCIL_BUFFER_BIT : 0;

	//setup all the layers this camera will render
	XmlNode layer = node.GetChild("renderlayers").FirstChild();
	while (!layer.IsNull())
	{
		//get the render layer
		unsigned int render_layer = layer.ValueInt();

		//set it up
		_Layers->SetCameraForLayer(this, render_layer);

		layer = layer.NextSibling();
	}

}

void Camera::OnStart()
{
	//add to vici camera list
	_Vici->_cameras.PushBack(this);

	//get a scene renderer
	_renderer = new Renderer();

	//initialize the scene
	_renderer->Init(this);

	//register for callbaks
	RegisterCallback(eUpdate, DELEGATE(Camera, Update, this));
}

void Camera::OnDestroy()
{
	//remove from vici camera list
	_Vici->_cameras.Remove(this);

	//delete renderer
	delete (_renderer);

	//call parents on destroy
	IComponent::OnDestroy();
}
//set up before rendinger
void Camera::PrepareScene()
{
	//clear appropriate buffers
	_renderer->ClearBuffer(_clear_flags, _clear_color);

	//load matrix identity   
	_renderer->_ms->Identity();

	//set up projection matrices
	_projection_mat = glm::perspective<float>(45.0f, _Display->AspectRatio(), 0.1f, 100.0f);

	//_view_mat = glm::translate(_view_mat, glm::vec3(0, 0, 10));

	_view_mat = glm::lookAt(_transform->GetPosition(), //set position
							_transform->GetPosition() + glm::vec3(_transform->ForwardDirection()), // and looks at the origin
							glm::vec3(0, 1, 0)  // set world up
							);

	//specify the view and projection matrices
	_renderer->_ms->SetProjection(_projection_mat);
	_renderer->_ms->SetView(_view_mat);
}

void Camera::Render()
{
	TLIST_foreach(GameObject*, obj, _render_list)
	{
		//push a matrix
		_renderer->_ms->PushMatrix();

		//apply model matrix
		_renderer->_ms->ApplyMatrix(obj->GetTransform()->GetModelMatrix());

		//set the MVP matrices in the matrix stack
		obj->PreRender(_renderer);
		obj->Render(_renderer);
		obj->PostRender(_renderer);

		//pop if off the stack
		_renderer->_ms->PopMatrix();
	}
}

void Camera::AddGameObject(GameObject* go)
{
	_render_list.PushBack(go);
}
void Camera::RemoveGameObject(GameObject* go)
{
	_render_list.Remove(go);
}

void Camera::Update()
{
	//rotate
	static float rot = _transform->GetRotation().y;
	if(_Input->KeyDown(GLFW_KEY_A))
	{
		rot -=2;
	}
	else if (_Input->KeyDown(GLFW_KEY_D))
	{
		rot +=2;
	}

	_transform->Rotate(rot, 0, 1, 0);

	//forward back
	if (_Input->KeyDown(GLFW_KEY_W))
	{
		_transform->Translate(glm::vec3(_transform->ForwardDirection()) * _speed);
		_speed += 0.005f;
	}
	else if (_Input->KeyDown(GLFW_KEY_S))
	{
		_transform->Translate(glm::vec3(-_transform->ForwardDirection()) * _speed);
		_speed += 0.005f;
	}
	else
	{
		_speed = 0.05f;
	}

	//up down
	if (_Input->KeyDown(GLFW_KEY_R))
	{
		_transform->Translate(0, 1 * _speed, 0);
		_speed += 0.005f;
	}
	else if (_Input->KeyDown(GLFW_KEY_F))
	{
		_transform->Translate(0, -1 * _speed, 0);
		_speed += 0.005f;
	}
}