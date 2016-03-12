#pragma once

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
};

template<typename T>
T* VSingleton<T>::Instance = nullptr;