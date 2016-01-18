#include "Transform.h"

Transform::Transform()
{
	bUpdateModelMatrix = true;
	//default scale
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
}
Transform::~Transform()
{

}

/* Transforms */
void Transform::Translate(glm::vec3 offset)
{
	Pos += offset;
	bUpdateModelMatrix = true;
}
void Transform::Translate(float x, float y, float z)
{
	Pos += glm::vec3(x, y, z);
	bUpdateModelMatrix = true;
}
void Transform::SetScale(float scale)
{
	Scale = glm::vec3(scale, scale, scale);
	bUpdateModelMatrix = true;
}
void Transform::SetScale(float scale_x, float scale_y, float scale_z)
{
	Scale = glm::vec3(scale_x, scale_y, scale_z);
	bUpdateModelMatrix = true;
}
void Transform::SetScale(glm::vec3 scale)
{
	Scale = scale;
	bUpdateModelMatrix = true;
}
void Transform::Rotate(float angle, glm::vec3 axis)
{
	Rotation = glm::vec3(angle * axis.x, angle * axis.y, angle * axis.z);
	bUpdateModelMatrix = true;
}
void Transform::Rotate(float angle, float ax_x, float ax_y, float ax_z)
{
	Rotation = glm::vec3(angle * ax_x, angle * ax_y, angle * ax_z);
	bUpdateModelMatrix = true;
}

glm::mat4 Transform::GetModelMatrix()
{
	UpdateMatrix();
	return Model;
}

void Transform::UpdateMatrix()
{
	//only do all this calculation if we need to
	if (bUpdateModelMatrix)
	{
		//reset
		Model = glm::mat4x4();
		RotationMatrix = glm::mat4x4();

		//translate
		Model = glm::translate(Model, Pos);

		//rotate
		RotationMatrix = glm::rotate(RotationMatrix, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		RotationMatrix = glm::rotate(RotationMatrix, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		RotationMatrix = glm::rotate(RotationMatrix, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		//multiple model by rotation
		Model = Model * RotationMatrix;

		//scale
		Model = glm::scale(Model, Scale);

		//set back to false
		bUpdateModelMatrix = false;
	}
}