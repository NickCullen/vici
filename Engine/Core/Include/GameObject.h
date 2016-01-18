#ifndef V_GAMEOBJECT
#define V_GAMEOBJECT

#include "Transform.h"
#include "Hash.h"
#include <vector>
#include "EComponentCallback.h"
#include "IComponent.h"

class CORE_API ComponentReference
{
public:
	IComponent* _pointer;
	Hash _component_type;

	ComponentReference(IComponent* component, Hash type)
	{
		_pointer = component;
		_component_type = type;
	}

	template<class Archive>
	void serialize(Archive& ar)
	{
		_SERIALIZE_VAR(_component_type, ar);
	}
};

typedef std::vector<ComponentReference> ComponentList;

/** 
* This class is the building block for the engine as it holds the components which
* Act upon the game object and others
*/

class CORE_API GameObject : public Object
{
	friend class Vici;

private:
	Transform _transform; /**< Transform containing position, rotation and scale of the object */

	ComponentList _components; /**< Map of components */

public:
	
	//template<class Archive>
	//void serialize(Archive& ar)
	//{
	//	_SERIALIZE_PARENT(Object, ar);
	//	_SERIALIZE_VAR(_transform, ar);
		//_SERIALIZE_VAR(_components, ar);
	//}

	template<class Archive>
	void load(Archive& ar)
	{
		_SERIALIZE_PARENT(Object, ar);
		_SERIALIZE_VAR(_transform, ar);
		_SERIALIZE_VAR(_components, ar);
	}

	template<class Archive>
	void save(Archive& ar) const
	{
		_SERIALIZE_PARENT(Object, ar);
		_SERIALIZE_VAR(_transform, ar);
		_SERIALIZE_VAR(_components, ar);
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

	/**
	* Creates the specified component and returns a reference too it
	* @param type The type of component
	* @return Pointer to component
	*/
	template<class T>
	T* AddComponent(Hash componentName)
	{
		T* comp = ComponentFactory::CreateComponent<T>(componentName);

		_components.push_back(ComponentReference(comp, componentName));

		//_components.insert(std::pair<Hash, SharedReference<IComponent>>(componentName, SharedReference<IComponent>(comp)));

		return comp;
	}
};

#endif