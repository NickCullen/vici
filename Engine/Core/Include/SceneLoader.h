#ifndef V_SCENELOADER
#define V_SCENELOADER

#include "CoreAPI.h"
#include "Singleton.h"
#include "VHash.h"
#include <vector>
#include "Serialization.h"
#include <string>

#define _SceneLoader Singleton<SceneLoader>::Instance()

/*Forward Decl*/
class Vici;

/** 
* structure used as a node in SceneLoader to hold scene file information and id 
*/

struct CORE_API SceneData
{
	VHash _id; /**< the hash id of the scene */
	std::string _scene_file; /**< the relative path to the scene xml file */
	std::string _scene_assets; /**< the relative path to the scene assets file */
};

/**
* Static class that is in charge of loading and transitioning between states 
* is has full control of the GameObject list found in the Vici engine class
* status (ongoing) 
*/

class CORE_API SceneLoader : public Singleton<SceneLoader>, ISerializable
{
friend class Vici;
private:
	int32 _current_level;	/**< integer containing the index into the _scenes list for the currently loaded scene */
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

	/**
	* Static thread function to load assets
	*/
	static void* LoadAssets(void* args);

	/**
	* Static thread function to load game objects
	*/
	static void* LoadObjects(void* args);
public:

	/**
	* Default constructor
	*/
	SceneLoader();

	/** 
	* Default destructor 
	*/
	~SceneLoader();
	
	virtual void Serialize(ArchiveOut& archive);
	virtual void Deserialize(ArchiveIn& archive);
	
	/**
	* function to load the scene by its index into the _scenes array
	* @param index unsigned integer index into the _scenes array 
	*/
	void LoadScene(int32 index);

	/**
	* Overloaded LoadScene function to load scene by string instead of by index
	* it will convert the string to a hash and search for it in the _scenes list
	* if found it will get its index and call LoadScene(int)
	* @param scene string containing the id of the required scene to load
	*/
	void LoadScene(char* scene);
};

#endif