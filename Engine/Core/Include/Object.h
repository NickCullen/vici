#ifndef V_OBJECT
#define V_OBJECT

#include "CoreAPI.h"
#include "VHash.h"

/**
* Base class of most objects used for fast == operator and 
* specifying indestructable objects 
* status (near complete?)
*/

class CORE_API Object
{
	friend class SceneLoader;
private:
	static unsigned int _count;	/**< static unsigned int containing the total number of Objects ever instantiated */

	unsigned int _instance; /**< the instance id for this Object */
	
	bool _indestructable;	/**< flag specifying if this Object is indestructable or not */

	bool _garbage; /**< Flag to represent if this object is garbage or not */
protected:

	VHash _hash; /**< The hash id of this object */
public:
	/**
	* Constructor for Object - will set _instance = _count++ when created 
	*/
	Object();	

	/**
	* Destructor for Object
	*/
	virtual ~Object();	

	/**
	* Copy constructor for Object used to ensure _count isnt incremented and _instance is copied
	* when copying over from another Object
	* @param other the reference to the Object being copied
	*/
	Object(const Object& other);

	/**
	* overridable == operator
	*/
	virtual bool operator==(Object& o);

	/** 
	* overidable != operator
	*/
	virtual bool operator!=(Object& o);

	/** 
	* Sets the current object to be indestructable 
	*/
	void MakeIndestructable();

	/**
	* Get function for the indestructable flag
	* @return returns true of false depending upon if the current object is indestructable or not
	*/
	inline bool Indestructable()
	{
		return _indestructable;
	}

	/**
	* Checks to see if the object is garbage
	* @return Boolean true if garbage false if not
	*/
	inline bool IsGarbage()
	{
		return _garbage;
	}

	/**
	* Sets the object to be garbage
	*/
	void SetGarbage()
	{
		_garbage = true;
	}

	/**
	* Getter for _id
	* @return Returns the hash value of the id for this Object
	*/
	inline VHash ID()
	{
		return _hash;
	}

	/**
	* virtual method that is called when an Object is destroyed
	* Any class that inherits from Object can implement this method
	*/
	virtual void OnDestroy(){};

	/**
	* Static class that will call the OnDestory method (and destroy) and object
	* if it is not indestructable
	*/
	static void Destroy(Object* o);
};

#endif