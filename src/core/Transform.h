#ifndef V_TRANSFORM
#define V_TRANSFORM

/*Forward decl*/

#include "glm.h"
#include "Xml.h"

/**
* Transform containing information on moving and representing the object in the world
* this is newly implemented and will change alot so there won't be much documentation until I 
* am satisfied with the way it is working. 
* Status(incomplete - new)
*/

class Transform
{
private:
	glm::vec3 _pos;
	glm::vec3 _scale;
	glm::vec3 _rotation;

	glm::mat4x4 _model;

	glm::mat4x4 _rotation_matrix;

	bool _update_model_matrix;
public:
	Transform();
	~Transform();

	//init from xml node
	void Init(XmlNode& node);

	/*Transforms*/
	void Translate(glm::vec3 offset);
	void Translate(float x, float y, float z);
	void Scale(float scale);
	void Scale(float scale_x, float scale_y, float scale_z);
	void Scale(glm::vec3 scale);
	void Rotate(float angle, glm::vec3 axis);
	void Rotate(float angle, float ax_x, float ax_y, float ax_z);

	//returns model matrix
	glm::mat4 GetModelMatrix();

	//getters
	inline glm::vec3 GetPosition()
	{
		return _pos;
	}

	inline glm::vec3 GetRotation()
	{
		return _rotation;
	}

	inline glm::vec3 GetScale()
	{
		return _scale;
	}

	inline glm::vec4 ForwardDirection()
	{
		static glm::vec4 initial_direction(0.0f,0.0f,-1.0f,1.0f);
		UpdateMatrix();
		return initial_direction * _rotation_matrix;
	}

	void UpdateMatrix();
};

#endif