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
	Singleton()
	{
        assert(Singleton<T>::_instance == NULL);

		if(Singleton<T>::_instance == NULL)
		{
			_instance = (T*)this;
		}
	}

	/**
	* Default destructor
	*/
	virtual ~Singleton()
	{
		_instance = NULL;
	}

	/**
	* Method for accessing the instance
	* @return Pointer to the instance
	*/
	static inline T* Instance() 
	{
		if (_instance == NULL)
			_instance = new T();
		return _instance;
	}
};

//static init
template<typename T> 
T* Singleton<T>::_instance = NULL;

#endif