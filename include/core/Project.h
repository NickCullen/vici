#ifndef V_PROJECT
#define V_PROJECT

#include "Singleton.h"

/**
 * Singleton class that all projects will 
 * derive from. Implement methods such as component
 * registration and asset importers. As well as other
 * things that may be needed (will update this when 
 * I know what they are...
 */

class Project : public Singleton<Project>
{
private:

	/**
	* Instance implementation of register component function
	*/
	virtual void Project_RegisterComponents() = 0;

	/**
	* Instance implementation of register asset importers
	*/
	virtual void Project_RegisterAssetImporters() = 0;

protected:

public:
	
	/**
	* Default constructor
	*/
	Project();

	/**
	* Default destructor
	*/
	virtual ~Project();

	/**
	* Static method to call the project implementation method
	* for registering components
	*/
	inline static void RegisterComponents()
	{ 
		Instance()->Project_RegisterComponents(); 
	}

	/**
	* Static method to call the project implementation method
	* for registering asset importers
	*/
	inline static void RegisterAssetImporters()
	{
		Instance()->Project_RegisterAssetImporters();
	}
};

#endif