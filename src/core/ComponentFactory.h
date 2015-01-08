#ifndef V_COMPONENT_FACTORY
#define V_COMPONENT_FACTORY

class IComponent;

/*for mapping of instances and creation functions*/
#include<map>
#include<string>

/*definition for the creation function of a component */
template<typename T> IComponent * CreateInstance() { return new T; }

/*the typedef for the hash table of mappings*/
typedef std::map<std::string, IComponent*(*)()> MapType;

/*Static class for component creation*/
class ComponentFactory
{
private:
	/*Static std::map to store all registered types*/
	static MapType* _types;

protected:
	/*Returns the std::map of all the registered types*/
	inline static MapType* GetTypes()
	{
		if (_types == NULL) _types = new MapType();
		return _types;
	}

public:
	ComponentFactory();
	~ComponentFactory();
	
	static IComponent* CreateComponent(std::string id)
	{
		MapType::iterator it = GetTypes()->find(id);
		if (it == GetTypes()->end())
			return 0;
		return it->second();
	}

	template<typename T>
	static T* CreateComponent(std::string id)
	{
		IComponent* comp = CreateComponent(id);
		return comp != NULL ? dynamic_cast<T>(comp) : NULL;
	}
};

/*this is the class used that each component will statically
* declare which will be used to register that type to the ComponentFactory*/
template<typename T>
class DerivedRegister : ComponentFactory
{
public:
	DerivedRegister(std::string s) 
	{
		GetTypes()->insert(std::make_pair(s, &CreateInstance<T>));
	}
};

#endif

