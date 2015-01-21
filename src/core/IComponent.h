#ifndef V_COMPONENT
#define V_COMPONENT

/*include the core engine */
#include "core.h"

/*Useful short hand macros*/
#define _transform _go->GetTransform()

/**
* The base class of all components. Components that do not require render callbacks should 
* inherit from this class, otherwise IDrawable should be used. 
*/

class IComponent
{
	/*friend classes to internal objects*/
	friend class Vici;
	friend class GameObject;
private:

protected:
	GameObject* _go; /**< The game object this component is attached to*/


public:

	/**
	* IComponent constructor
	*/
	IComponent();

	/**
	* IComponent destructor
	*/
	virtual ~IComponent(); 

	/**
	* Called when a component is created via xml. No references should be made to other 
	* components in this function as there is no guarantee that they may be instantiated yet.
	* note that components inheriting from this class MUST call IDrawable::Init(go, data)
	* @param go this component belongs to
	* @param data the xml node containing the required loading information
	*/
	virtual void Init(GameObject* go, rapidxml::xml_node<char>* data);

	/**
	* Called once when the component is created
	*/
	virtual void Awake(){};
	/**
	* Called once when the component is created but after Awake
	*/
	virtual void Start(){}; 
	/**
	* Called once per frame
	*/
	virtual void Update(){};
	/**
	* Called when game object becomes active
	*/
	virtual void OnEnable(){};
	/**
	* Called when game object becomes inactive
	*/
	virtual void OnDisable(){};
	
	/**
	* Components that require the logic functions (see above) will have to register
	* for them by calling RegisterCallback and passing in the required enum (see EComponentCallback)
	* this method is likely to change soon to take a function pointer - when this happens all the
	* logic functions won't be specified in IComponent; rather by the component themselves
	* @param callback enum specifying required callback
	*/
	void RegisterCallback(EComponentCallback callback);

	/**
	* Getter function to return the game object this component is attached to
	* @return pointer to the game object
	*/
	inline GameObject* GetGameObject()
	{
		return _go;
	}
};

#endif