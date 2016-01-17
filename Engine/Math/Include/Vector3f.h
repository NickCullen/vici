#pragma once

#include "MathAPI.h"
#include <glm/vec3.hpp>
#include "Serialization.h"

class MATH_API Vector3f : public glm::vec3
{
	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(x, y, z);
	}

};