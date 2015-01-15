#ifndef V_TRANSFORM
#define V_TRANSFORM

/*Forward decl*/

#include "glm.h"

class Transform
{
private:
	glm::vec3 _pos;
	glm::vec3 _scale;
	glm::vec3 _rotation;

public:
	Transform();
	~Transform();

	/*Transforms*/
	void Translate(glm::vec3 offset);
	void Translate(float x, float y, float z);
	void Scale(float scale);
	void Scale(float scale_x, float scale_y, float scale_z);
	void Scale(glm::vec3 scale);
	void Rotate(float angle, glm::vec3 axis);
	void Rotate(float angle, float ax_x, float ax_y, float ax_z);

	/*Camera and model calculations*/
	glm::mat4 GetMVP(glm::mat4& view, glm::mat4& projection);


};

#endif