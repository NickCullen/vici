#ifndef V_PROJECT
#define V_PROJECT

#include "Singleton.h"
#include "CoreAPI.h"

#define _Project Singleton<Project>::Instance()

/**
 * Singleton class that all projects will 
 * derive from. Implement methods such as component
 * registration and asset importers. As well as other
 * things that may be needed (will update this when 
 * I know what they are...
 */

class CORE_API Project : public Singleton<Project>
{

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
	* Instance implementation of register component function
	*/
    virtual void RegisterComponents(){};

	/**
	* Instance implementation of register asset importers
	*/
    virtual void RegisterAssetImporters(){};
};

#endif