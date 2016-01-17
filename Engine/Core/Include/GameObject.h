#ifndef V_GAMEOBJECT
#define V_GAMEOBJECT

#include "Object.h"
#include "Transform.h"
#include "Hash.h"
#include "Delegate.h"



//functions to be called
enum EComponentCallback { eUpdate, eOnEnable, eOnDisable, eMAX_CALL_COUNT};

/** 
* This class is the building block for the engine as it holds the components which
* Act upon the game object and others
*/

class CORE_API GameObject : public Object
{
	friend class Vici;

private:
	Transform _transform;

public:
	
	template<class Archive>
	void serialize(Archive& ar)
	{
		_SERIALIZE_PARENT(Object, ar);
		_SERIALIZE_VAR(_transform, ar);
	}

	/**
	* Default ctor
	*/
	GameObject();
	
	/**
	* Default dtor
	*/
	~GameObject();

	/**
	* @return Returns pointer to the transform
	*/
	inline Transform* GetTransform() { return &_transform; }

};

#endif