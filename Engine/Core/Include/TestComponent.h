#pragma once

#include "IComponent.h"

class TestComponent : public IComponent
{
	COMPONENT_REGISTER_DEF(TestComponent)
private:
	int _my_int;

public:
	TestComponent();

	~TestComponent();

	template<class Archive>
	void serialize(Archive& ar)
	{
		_SERIALIZE_VAR(_my_int, ar);
		_SERIALIZE_PARENT(IComponent, ar);
	}
};