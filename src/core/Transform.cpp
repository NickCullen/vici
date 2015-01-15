#include "Transform.h"

Transform::Transform()
{

}
Transform::~Transform()
{

}

/* Transforms */
void Transform::Translate(glm::vec3 offset)
{
	_pos += offset;
}
void Transform::Translate(float x, float y, float z)
{
	_pos += glm::vec3(x, y, z);
}
void Transform::Scale(float scale)
{
	_scale = glm::vec3(scale, scale, scale);
}
void Transform::Scale(float scale_x, float scale_y, float scale_z)
{
	_scale = glm::vec3(scale_x, scale_y, scale_z);
}
void Transform::Scale(glm::vec3 scale)
{
	_scale = scale;
}
void Transform::Rotate(float angle, glm::vec3 axis)
{
	//todo
}
void Transform::Rotate(float angle, float ax_x, float ax_y, float ax_z)
{
	//todo
}

/*Camera and model calculations*/
glm::mat4 Transform::GetMVP(glm::mat4& view, glm::mat4& projection)
{
	//construct model matrix
	glm::mat4 model = glm::mat4(1.0f);

	//return the mvp
	return projection * view * model;

}
