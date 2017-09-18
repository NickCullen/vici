#pragma once

/**
 * Base class to inherit from if you want
 * quick setup of a singleton
 */
template<typename T>
class TSingleton
{
private:
	static T* Instance;	/**< Pointer to the loaded instance */

public:
	/**
	 * Instantiates and returns T*
	 */
	static T* GetInstance();

};

// Static decl.
template<typename T>
T* TSingleton<T>::Instance = nullptr;

template<typename T>
T* TSingleton<T>::GetInstance()
{
	if (Instance == nullptr)
		Instance = new T;
	return Instance;
}