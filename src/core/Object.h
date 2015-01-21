#ifndef V_OBJECT
#define V_OBJECT

/**
* Base class of most objects used for fast == operator and 
* specifying indestructable objects 
* status (near complete?)
*/

class Object
{
	friend class SceneLoader;
private:
	static unsigned int _count;	/**< static unsigned int containing the total number of Objects ever instantiated */
	unsigned int _instance; /**< the instance id for this Object */
	
	bool _indestructable;	/**< flag specifying if this Object is indestructable or not */
protected:

public:
	/**
	* Constructor for Object - will set _instance = _count++ when created 
	*/
	Object();	

	/**
	* Destructor for Object
	*/
	~Object();	

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

};

#endif