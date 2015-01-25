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

class IComponent : public Object
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
	* Called when the component gets destroyed
	*/
	virtual void OnDestroy();

	/**
	* Components which require logic functions (See EComponentCallback) will
	* need to register for a callback by passing in a delegate and the type of callback they
	* require. Safe to use in Init function.
	* @param callback_type The enum specifying which callback is required (see EComponentCallback(
	* @param callback The delegate containing callback information (i.e. the method to call when the logic function is fired off)
	*/
	void RegisterCallback(EComponentCallback callback_type, Delegate callback);

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