#ifndef V_OBJECT
#define V_OBJECT

#include "CoreAPI.h"
#include "Hash.h"

/**
* Base class of most objects used for fast == operator and 
* specifying indestructable objects 
* status (near complete?)
*/

class CORE_API Object
{
	friend class SceneLoader;
private:
	static uint32 Count;	/**< static unsigned int containing the total number of Objects ever instantiated */

	uint32 InstanceID; 		/**< the instance id for this Object */
	
	bool bIndestructable;	/**< flag specifying if this Object is indestructable or not */

	bool bGarbage; /**< Flag to represent if this object is garbage or not */
protected:

	Hash MyHash; /**< The hash id of this object */
public:
	/**
	* Constructor for Object - will set _instance = _count++ when created 
	*/
	Object();	

	/**
	* Destructor for Object
	*/
	virtual ~Object();	

	template< class Archive>
	void serialize(Archive& ar)
	{
		_SERIALIZE_VAR(bIndestructable, ar)
		_SERIALIZE_VAR(MyHash, ar)
	}


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
	inline bool IsIndestructable()
	{
		return bIndestructable;
	}

	/**
	* Checks to see if the object is garbage
	* @return Boolean true if garbage false if not
	*/
	inline bool IsGarbage()
	{
		return bGarbage;
	}

	/**
	* Sets the object to be garbage
	*/
	void SetGarbage()
	{
		bGarbage = true;
	}

	/**
	* Getter for _id
	* @return Returns the hash value of the id for this Object
	*/
	inline Hash GetID()
	{
		return MyHash;
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

CEREAL_REGISTER_TYPE(Object);

#endif