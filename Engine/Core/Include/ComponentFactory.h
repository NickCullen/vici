#ifndef V_COMPONENT_FACTORY
#define V_COMPONENT_FACTORY

/* Forward Decl */
class IComponent;

/* for mapping of instances and creation functions */
#include "CoreAPI.h"
#include <map>
#include "Hash.h"
#include "SmartPtr.h"

/* definition for the creation function of a component */
template<class T> ComponentPtr Internal_Component_CreateInstance() { return std::make_shared<T>(); }

/* the typedef for the hash table of mappings */
typedef std::map<Hash, ComponentPtr(*)()> MapType;

/**
* Static class holding a Hashtable of registered component creation functions
* Used to instantiate components via strings.
* Status(Complete)
*/

class CORE_API ComponentFactory
{
private:
	static MapType* Types; /**< static hash table containing creation function for registered classes */

protected:

	/**
	* Getter function for returning the hashtable for registered components
	* @return Hashtable containing registered components
	*/
	inline static MapType* GetTypes()
	{
		if (Types == NULL) Types = new MapType();
		return Types;
	}

	/**
	* Internal function used to find a registered class' creation function on the hash table
	* @param id string containing id of required component
	* @return The found component (NULL if not found)
	*/
	static ComponentPtr FindType(Hash id);

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
	static ComponentPtr CreateComponent(Hash id);

	/**
	* Same as the non-template CreateComponent function except it casts the output to the 
	* type specified in <>. e.g. to create a camera component would be to write:
	* Camera* cam = ComponentFactory::CreateComponent<Camera>("Camera");
	* @param id string containing id of required component
	* @return The created component pointer of specified type (NULL if not created)
	*/
	template<class T>
	static ComponentPtrDef<T> CreateComponent(Hash id)
	{
		//IComponent* comp = CreateComponent(id);
		//return comp != NULL ? (T*)comp : NULL;
		ComponentPtr comp = CreateComponent(id);
		return comp != NULL ? std::dynamic_pointer_cast<T>(comp) : NULL;
	}
};

/**
* The ComponentRegister class is instantiated by every component to register their creation function
* so they can be instantiated later on (e.g. scene loading) via strings
* Status(Complete)
*/

template<class T>
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
	ComponentRegister(Hash s) 
	{
		GetTypes()->insert(std::make_pair(s, &Internal_Component_CreateInstance<T>));
	}
};

#endif

