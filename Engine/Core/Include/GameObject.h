#ifndef V_GAMEOBJECT
#define V_GAMEOBJECT

#include "Object.h"
#include "VHash.h"
#include "Xml.h"
#include "GameObjectTree.h"
#include "ComponentTree.h"
#include "Delegate.h"

/*Forward Decls*/
class Renderer;
class IComponent;
class Transform;
class IDrawable;
class MatrixStack;

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
	Transform* _t;	/**< Pointer to the transform of the GameObject holding its position, rotation and scale */

	ComponentTree _components; /**< tree of components attached to this object */

	TList<IDrawable*> _render_list;	/**< List of IDrawable components attached to this object (note these are also found in _components as an IComponent* type */

	TList<Delegate> _calls[eMAX_CALL_COUNT]; /**< List of delegate callbacks for classes which require logic function calls (see EComponentCallback and RegisterCallback) */

	bool _enabled;	/**< Flag to tell if this game object is enabled or not */

	uint32 _layer; /**< The unsigned integer to specify which layer this game object is on */

	GameObject* _parent; /**< The parent GameObject of this GameObject (can be NULL) */

	GameObjectTree _children; /**< tree of child GameObjects */

	bool _start_called; /**< Flag to set so we dont call OnStart more than once */
protected:

public:
	/**
	* GameObject Constructor
	*/
	GameObject();

	/**
	* GameObject Destructor 
	*/
	~GameObject();

	/**
	* Called when a game object is first created - here it will load up all its components and child nodes
	* note that no components should do any interaction with any other GameObject or Component in this function!
	* only self initilization and RegisterCallback functions should be used
	* @param parent A Pointer to the parent GameObject (Can be NULL if the initilizing GameObject is the root)
	* @param node The XML Node contaning init data for the GameObject
	*/
	void Init(GameObject* parent, XmlNode& node);

	/**
	* First call of the render process and called Before Render
	* @param renderer A pointer to the Render class which controls the actual render process
	*/
	void PreRender(Renderer* renderer);
	/**
	* Second call of the render process (after PreRender before PostRender)
	* @param renderer A pointer to the Render class which controls the actual render process
	*/
	void Render(Renderer* renderer);
	/**
	* Last call of the render process and called After Render
	* @param renderer A pointer to the Render class which controls the actual render process
	*/
	void PostRender(Renderer* renderer);

	/**
	* Apply the game objects transform (model matrix) to the matrix statck
	* @param stack A pointer containing the current matrix stack
	*/
	void ApplyModelMatrix(MatrixStack* stack);

	/**
	* Used for Components to regsiter a logic callback (see EComponentCallback) and is Safe to use in Components Init function
	* @param callback_type The enum specifying the required callback
	* @param callback The delegate containing callback information
	*/
	void RegisterCallback(EComponentCallback callback_type, Delegate callback);

	/**
	* Dispatches a logic function (will call all the registered delegates of said enum method)
	* @param method The enum specifying which logic function to execute
	*/
	void Dispatch(EComponentCallback method);

	/** 
	* As OnStart is a required method then we need to 
	* dispatch this as a specified method in GameObject
	*/
	void OnStart();

	/**
	* Sets the _enabled flag to the input bool. This will fire off OnEnabled or OnDisabled logic functions
	* (See EComponentCallback) if the flag changes
	* @param flag The input bool to set _enabled flag
	*/
	void SetEnabled(bool flag);

	/**
	* Returns the value of _enabled flag
	* @return Return is a boolean (true if enabled false if not)
	*/
	inline bool GetEnabled()
	{
		return _enabled;
	}

	/**
	* Specifys which layer the game object is on
	* @return An unsigned integer containing which layer this game object is on
	*/
	inline uint32 GetLayer()
	{
		return _layer;
	}

	/**
	* Getter for Transform
	* @return Returns the transform for the GameObject
	*/
	inline Transform* GetTransform()
	{
		return _t;
	}


	/**
	* Getter for the render list of this game object. This contains all the IDrawable
	* Components attached to this game object
	* @return Returns a pointer to the RenderList
	*/
	inline TList<IDrawable*>* RenderList()
	{
		return &_render_list;
	}
	
	/**
	* Called when a game object is being destroyed
	*/
	void OnDestroy();

	/**
	* Used to attach a component to the components list
	* @param comp The component to attached to the object
	*/
	void AddComponent(IComponent* comp);

	/**
	* Removes the specified component from the components list
	* @param comp The component to be removed
	*/
	void RemoveComponent(IComponent* comp);

	/**
	* Searches and finds a component of given type
	* @param component The type id of the Component you want to find This 
	* is the string representation of the component type name
	*/
	IComponent* FindComponent(VHash type_id);

	/**
	* Works the same as FindComponent except it casts it to the given type
	* Note that this will return NULL if component wasn't found!
	* @param component The type id of the Component you want to find This
	* is the string representation of the component type name
	*/
	template<typename T>
	inline T* FindComponent(VHash type_id){ return (T*)FindComponent(type_id); }
};

#endif