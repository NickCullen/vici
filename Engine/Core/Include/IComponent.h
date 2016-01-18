#ifndef V_COMPONENT
#define V_COMPONENT

/*include the core engine */
#include "ComponentFactory.h"
#include "EComponentCallback.h"
#include "Object.h"
#include "Delegate.h"
#include "SmartPtr.h"

// Forward decl.
class GameObject;

/*Useful short hand macros*/
//#define _transform _go->GetTransform()

// Definition for classes that inherit from IComponent to put at the
// Top of their definition
#define COMPONENT_REGISTER_DEF(Type) \
	public: \
		static ComponentRegister<Type> reg; \
		static void Register() { \
			reg = ComponentRegister<Type>(#Type); \
		} \

/**
* The base class of all components. Components that do not require render callbacks should 
* inherit from this class, otherwise IDrawable should be used. 
*/

class CORE_API IComponent
{
	/*friend classes to internal objects*/
	friend class Vici;
private:

protected:
	GameObject* MyGameObject; /**< The game object this component is attached to*/

public:

	/**
	* IComponent constructor - this should be used to setup
	* initiale member variables of the component
	*/
	IComponent();

	/**
	* IComponent destructor
	*/
	virtual ~IComponent(); 

	template<class Archive>
	void serialize(Archive& ar)
	{
		//_SERIALIZE_VAR(_go, ar);
		//_SERIALIZE_PARENT(Object, ar);
	}

	/**
	* Called when the component is created (after init IF the component was loaded
	* from xml). It is safe to register for callbacks here and reference other components 
	* and game objects
	*/
	virtual void OnStart();

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
	GameObject* GetGameObject();

	/**
	* Sets the GameObject that this component is attached to
	* @param go The GameObject that this component is attached to
	*/
	inline void SetGameObject(GameObject* go);
};

#endif