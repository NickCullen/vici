#pragma once

#include "IComponent.h"

class CORE_API TestComponent : public IComponent
{
	COMPONENT_REGISTER_DEF(TestComponent)
private:
	int MyInt;

public:
	TestComponent();

	~TestComponent();

	template<class Archive>
	void serialize(Archive& ar)
	{
		_SERIALIZE_VAR(MyInt, ar);
		_SERIALIZE_PARENT(IComponent, ar);
	}

	/*template<class Archive>
	void load(Archive& ar)
	{
		_SERIALIZE_VAR(_my_int, ar);
		_SERIALIZE_PARENT(IComponent, ar);
	}*/
};

CEREAL_REGISTER_TYPE(TestComponent);