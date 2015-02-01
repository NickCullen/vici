#include "Transform.h"

Transform::Transform()
{
	_update_model_matrix = true;
	//default scale
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);
}
Transform::~Transform()
{

}

void Transform::Init(rapidxml::xml_node<char>* node)
{
	//make sure node exists
	if (node != NULL)
	{
		//get nodes
		rapidxml::xml_node<char>* position_node = node->first_node("position");
		rapidxml::xml_node<char>* rotation_node = node->first_node("rotation");
		rapidxml::xml_node<char>* scale_node = node->first_node("scale");

		//load values
		if (position_node != NULL)
		{
			char* data = position_node->value();
			sscanf(data, "%f %f %f", &_pos[0], &_pos[1], &_pos[2]);
		}

		if (rotation_node != NULL)
		{
			char* data = rotation_node->value();
			sscanf(data, "%f %f %f", &_rotation[0], &_rotation[1], &_rotation[2]);
		}

		if (scale_node != NULL)
		{
			char* data = scale_node->value();
			sscanf(data, "%f %f %f", &_scale[0], &_scale[1], &_scale[2]);
		}

	}
}
/* Transforms */
void Transform::Translate(glm::vec3 offset)
{
	_pos += offset;
	_update_model_matrix = true;
}
void Transform::Translate(float x, float y, float z)
{
	_pos += glm::vec3(x, y, z);
	_update_model_matrix = true;
}
void Transform::Scale(float scale)
{
	_scale = glm::vec3(scale, scale, scale);
	_update_model_matrix = true;
}
void Transform::Scale(float scale_x, float scale_y, float scale_z)
{
	_scale = glm::vec3(scale_x, scale_y, scale_z);
	_update_model_matrix = true;
}
void Transform::Scale(glm::vec3 scale)
{
	_scale = scale;
	_update_model_matrix = true;
}
void Transform::Rotate(float angle, glm::vec3 axis)
{
	_rotation = glm::vec3(angle * axis.x, angle * axis.y, angle * axis.z);
	_update_model_matrix = true;
}
void Transform::Rotate(float angle, float ax_x, float ax_y, float ax_z)
{
	_rotation = glm::vec3(angle * ax_x, angle * ax_y, angle * ax_z);
	_update_model_matrix = true;
}

glm::mat4 Transform::GetModelMatrix()
{
	//only do all this calculation if we need to
	if (_update_model_matrix)
	{
		_model = glm::mat4x4();

		//transltae
		_model = glm::translate(_model, _pos);

		//rotation
		_model = glm::rotate(_model, _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		_model = glm::rotate(_model, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		_model = glm::rotate(_model, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

		//scale
		_model = glm::scale(_model, _scale);

		//set back to false
		_update_model_matrix = false;
	}

	return _model;
}
