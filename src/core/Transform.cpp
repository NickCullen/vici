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

void Transform::Init(XmlNode& node)
{
	//make sure node exists
	if (!node.IsNull())
	{
		//get nodes
		XmlNode position_node = node.GetChild("position");
		XmlNode rotation_node = node.GetChild("rotation");
		XmlNode scale_node = node.GetChild("scale");

		//load values
		if (!position_node.IsNull())
		{
			sscanf(position_node.ValueString(), "%f %f %f", &_pos[0], &_pos[1], &_pos[2]);
		}

		if (!rotation_node.IsNull())
		{
			sscanf(rotation_node.ValueString(), "%f %f %f", &_rotation[0], &_rotation[1], &_rotation[2]);
		}

		if (!scale_node.IsNull())
		{
			sscanf(scale_node.ValueString(), "%f %f %f", &_scale[0], &_scale[1], &_scale[2]);
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
	UpdateMatrix();
	return _model;
}

void Transform::UpdateMatrix()
{
	//only do all this calculation if we need to
	if (_update_model_matrix)
	{
		_model = glm::mat4x4();

		//transltae
		_model = glm::translate(_model, _pos);

		_rotation_matrix = glm::mat4x4(1.0f);

		//rotation
		_rotation_matrix = glm::rotate(_rotation_matrix, _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		_rotation_matrix = glm::rotate(_rotation_matrix, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		_rotation_matrix = glm::rotate(_rotation_matrix, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

		_model = _model * _rotation_matrix;

		//scale
		_model = glm::scale(_model, _scale);

		//set back to false
		_update_model_matrix = false;
	}
}