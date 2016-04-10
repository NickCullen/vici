#pragma once

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

};

template<typename SingletonType>
SingletonType* VSingleton<SingletonType>::Instance = nullptr;

