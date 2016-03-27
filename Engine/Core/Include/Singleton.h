#pragma once

#include "Reflection.h"

template<typename T>
class VSingleton
{
private:
	static T* Instance;

public:

	VSingleton(T* instance)
	{
		Instance = instance;
	}

	static T* GetInstance()
	{
		if (Instance == nullptr)
			Instance = new T;
		return Instance;
	}

	static void Register()
	{

		//Class::declare<VSingleton<T>>("VSingleton");

		/*Class::declare<VSingleton>("VSingleton")
			.constructor()
			.property("Instance", &VSingleton::GetInstance)
			;*/
	}
};

template<typename T>
T* VSingleton<T>::Instance = nullptr;

