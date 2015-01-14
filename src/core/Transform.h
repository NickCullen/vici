#ifndef V_TRANSFORM
#define V_TRANSFORM

/*Forward decl*/

#include "glm/glm.hpp"

class Transform
{
private:
	glm::vec4 _pos;
	glm::vec4 _scale;
	glm::vec4 _rotation;

public:
	Transform();
	~Transform();
};

#endif