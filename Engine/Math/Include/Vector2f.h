#pragma once

#include "MathAPI.h"
#include <glm/vec2.hpp>
#include "Serialization.h"

class MATH_API Vector2f : public glm::vec2
{
	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(x, y);
	}

};