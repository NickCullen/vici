#ifndef V_COMPONENT_FACTORY
#define V_COMPONENT_FACTORY

/* Forward Decl */
class IComponent;

/* for mapping of instances and creation functions */
#include "CoreAPI.h"
#include <map>
#include "VHash.h"

/* definition for the creation function of a component */
template<typename T> IComponent* Internal_Component_CreateInstance() { return new T; }

/* the typedef for the hash table of mappings */
typedef std::map<VHash, IComponent*(*)()> MapType;

/**
* Static class holding a Hashtable of registered component creation functions
* Used to instantiate components via strings.
* Status(Complete)
*/

class CORE_API ComponentFactory
{
private:
	static MapType* _types; /**< static hash table containing creation function for registered classes */  

protected:

	/**
	* Getter function for returning the hashtable for registered components
	* @return Hashtable containing registered components
	*/
	inline static MapType* GetTypes()
	{
		if (_types == NULL) _types = new MapType();
		return _types;
	}

	/**
	* Internal function used to find a registered class' creation function on the hash table
	* @param id string containing id of required component
	* @return The found component (NULL if not found)
	*/
	static IComponent* FindType(VHash id);

public:

	/**
	* Not Used
	*/
	ComponentFactory();
	/**
	* Not Used
	*/
	~ComponentFactory();
	
	/**
	* Cleans up component creation functions on the list when the program ends
	*/
	static void CleanUp();

	/**
	* Function that instantiates a component given the id
	* @param id string containing id of required component
	* @return The created component pointer (NULL if not created)
	*/
	static IComponent* CreateComponent(VHash id);

	/**
	* Same as the non-template CreateComponent function except it casts the output to the 
	* type specified in <>. e.g. to create a camera component would be to write:
	* VCamera* cam = ComponentFactory::CreateComponent<VCamera>("VCamera");
	* @param id string containing id of required component
	* @return The created component pointer of specified type (NULL if not created)
	*/
	template<typename T>
	static T* CreateComponent(VHash id)
	{
		IComponent* comp = CreateComponent(id);
		return comp != NULL ? (T*)comp : NULL;
	}
};

/**
* The ComponentRegister class is instantiated by every component to register their creation function
* so they can be instantiated later on (e.g. scene loading) via strings
* Status(Complete)
*/

template<typename T>
class CORE_API ComponentRegister : ComponentFactory
{
public:
	/**
	* The constructor used by the component to register its creation function
	* for example, if I want to register a component called 'MyComponent' I would create a static 
	* ComponentRegister member variable called 'reg' and in my projects "RegisterComponents" function I can register
	* the class as follows:
	* MyComponent::reg = ComponentRegister<MyComponent>("MyComponent");
	* @param s string containing id of required component, this normally represents the class name
	*/
	ComponentRegister(VHash s) 
	{
		GetTypes()->insert(std::make_pair(s, &Internal_Component_CreateInstance<T>));
	}
};

#endif

