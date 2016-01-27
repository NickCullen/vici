#ifndef V_GAMEOBJECT
#define V_GAMEOBJECT

#include "Transform.h"
#include "Hash.h"
#include <vector>
#include "EComponentCallback.h"
#include "IComponent.h"

typedef std::vector<ComponentPtr> ComponentList;

/** 
* This class is the building block for the engine as it holds the components which
* Act upon the game object and others
*/

class CORE_API GameObject : public Object
{
	friend class Vici;

private:
	Transform MyTransform; /**< Transform containing position, rotation and scale of the object */

	ComponentList Components; /**< Map of components */

	/**
	 * Internal call by Vici class
	 */
	void Initialize();

public:
	
	template<class Archive>
	void serialize(Archive& ar)
	{
		_SERIALIZE_PARENT(Object, ar);
		_SERIALIZE_VAR(MyTransform, ar)
		_SERIALIZE_VAR(Components, ar)
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
	inline Transform* GetTransform() { return &MyTransform; }

	/**
	* Creates the specified component and returns a reference too it
	* @param type The type of component
	* @return Pointer to component
	*/
	template<class T>
	T* AddComponent(Hash componentName)
	{
		ComponentPtr comp = ComponentFactory::CreateComponent<T>(componentName);

		if (comp != NULL)
		{
			
			Components.push_back(comp);


		}

		return (T*)comp.get();
	}
};

CEREAL_REGISTER_TYPE(GameObject);

#endif