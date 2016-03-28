#pragma once

#include "Reflection.h"

template<typename SingletonType>
class VSingleton
{
private:
	static SingletonType* Instance;

public:

	VSingleton(SingletonType* instance)
	{
		Instance = instance;
	}

	static SingletonType* GetInstance()
	{
		if (Instance == nullptr)
			Instance = new SingletonType;
		return Instance;
	}

	static void Register()
	{
		//ponder::Class::declare<VSingleton<T>>("VSingleton<VEngine>")
			//.
			//.property("Instance", &VSingleton<T>::GetInstance);

	}
};

template<typename SingletonType>
SingletonType* VSingleton<SingletonType>::Instance = nullptr;

