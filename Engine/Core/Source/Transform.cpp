#include "Transform.h"

Transform::Transform()
{
	bUpdateModelMatrix = true;
	//default scale
	Scale = Vector3f(1.0f, 1.0f, 1.0f);
}
Transform::~Transform()
{

}

/* Transforms */
void Transform::Translate(const Vector3f& offset)
{
	Pos = Pos + offset;
	bUpdateModelMatrix = true;
}
void Transform::Translate(float x, float y, float z)
{
	Pos = Pos + Vector3f(x, y, z);
	bUpdateModelMatrix = true;
}
void Transform::SetScale(float scale)
{
	Scale = Vector3f(scale, scale, scale);
	bUpdateModelMatrix = true;
}
void Transform::SetScale(float scale_x, float scale_y, float scale_z)
{
	Scale = Vector3f(scale_x, scale_y, scale_z);
	bUpdateModelMatrix = true;
}
void Transform::SetScale(const Vector3f& scale)
{
	Scale = scale;
	bUpdateModelMatrix = true;
}
void Transform::Rotate(float angle, const Vector3f& axis)
{
	Rotation = Vector3f(angle * axis.x, angle * axis.y, angle * axis.z);
	bUpdateModelMatrix = true;
}
void Transform::Rotate(float angle, float ax_x, float ax_y, float ax_z)
{
	Rotation = Vector3f(angle * ax_x, angle * ax_y, angle * ax_z);
	bUpdateModelMatrix = true;
}

Matrix4f& Transform::GetModelMatrix()
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
		Model = Matrix4f::Identity();
		RotationMatrix = Matrix4f::Identity();

		THROW_NOT_IMPL

		////translate
		//Model = glm::translate(Model, Pos);
		//
		////rotate
		//RotationMatrix = glm::rotate(RotationMatrix, glm::radians(Rotation.x), Vector3f(1.0f, 0.0f, 0.0f));
		//RotationMatrix = glm::rotate(RotationMatrix, glm::radians(Rotation.y), Vector3f(0.0f, 1.0f, 0.0f));
		//RotationMatrix = glm::rotate(RotationMatrix, glm::radians(Rotation.z), Vector3f(0.0f, 0.0f, 1.0f));

		////multiple model by rotation
		//Model = Model * RotationMatrix;

		////scale
		//Model = glm::scale(Model, Scale);

		////set back to false
		//bUpdateModelMatrix = false;
	}
}