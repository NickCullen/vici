#ifndef V_SINGLETON
#define V_SINGLETON

#include "PlatformDefinitions.h"

/**
* Class to derive from if you want it to
* become a singleton class
*/

template<typename T>
class Singleton
{
private:
	static T* _instance;	/**< The instance */
protected:

public:
	/**
	* Default constructor that will assert if 
	* There is already an instance of class T
	* @param instance The pointer to the instance of the singleton
	*/
	Singleton(T* instance)
	{
        assert(Singleton<T>::_instance == NULL);

		if(Singleton<T>::_instance == NULL)
		{
			Singleton<T>::_instance = instance;
		}
	}

	/**
	* Default destructor
	*/
	~Singleton(){};

	/**
	* Method for accessing the instance
	* @return Pointer to the instance
	*/
	static inline T* Instance() 
	{
		return Singleton<T>::_instance;
	}
};

//static init
template<typename T> 
T* Singleton<T>::_instance = NULL;

#endif