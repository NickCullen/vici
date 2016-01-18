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
	static T* ThisInstance;	/**< The instance */
protected:

public:
	Singleton()
	{
        assert(Singleton<T>::ThisInstance == NULL);

		if(Singleton<T>::ThisInstance == NULL)
		{
			ThisInstance = (T*)this;
		}
	}

	/**
	* Default destructor
	*/
	virtual ~Singleton()
	{
		ThisInstance = NULL;
	}

	/**
	* Method for accessing the instance
	* @return Pointer to the instance
	*/
	static inline T* Instance() 
	{
		if (ThisInstance == NULL)
			ThisInstance = new T();
		return ThisInstance;
	}
};

//static init
template<typename T>
T* Singleton<T>::ThisInstance = NULL;

#endif