#ifndef V_SCENELOADER
#define V_SCENELOADER

#include "Singleton.h"
#include "VHash.h"
#include <vector>

/*Forward Decl*/
class Vici;

/** 
* structure used as a node in SceneLoader to hold scene file information and id 
*/

struct SceneData
{
	VHash _id; /**< the hash id of the scene */
	char _scene_file[512]; /**< the full path to the scene xml file */
	char _scene_assets[512]; /**< the full path to the scene assets file */
};

/**
* Static class that is in charge of loading and transitioning between states 
* is has full control of the GameObject list found in the Vici engine class
* status (ongoing) 
*/

class SceneLoader : public Singleton<SceneLoader>
{
friend class Vici;
private:
	int _current_level;	/**< integer containing the index into the _scenes list for the currently loaded scene */
	std::vector<SceneData> _scenes; /**< list of SceneData nodes */

	/** 
	* initialized when the engine starts. Can only be called from Vici class
	*/
	void Init();

	/**
	* Only callable by SceneLoader and will unload all destructable objects in the current scene
	* upon transitioning to the new scene
	*/
	void UnloadCurrentScene();
public:

	/**
	* Unused constructor
	*/
	SceneLoader();

	/** 
	* Unused destructor 
	*/
	virtual ~SceneLoader();

	/**
	* function to load the scene by its index into the _scenes array
	* @param index unsigned integer index into the _scenes array 
	*/
	void LoadScene(unsigned int index);

	/**
	* Overloaded LoadScene function to load scene by string instead of by index
	* it will convert the string to a hash and search for it in the _scenes list
	* if found it will get its index and call LoadScene(int)
	* @param scene string containing the id of the required scene to load
	*/
	void LoadScene(char* scene);
};

#endif