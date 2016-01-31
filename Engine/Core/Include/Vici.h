#ifndef VICI_H
#define VICI_H

// Required Includes 
#include "CoreAPI.h"

#include "Platform.h"
#include "Input.h"

#include "GameObject.h"

// Macros 
#define _Vici Singleton<Vici>::Instance()
#define _TYPE_NAME(_type) #_type

// Typedefs
typedef std::vector<GameObjectPtr> GameObjectList;

// 
/**
* The core of the engine - A singelton class that can be accessed by anything via the 
* _Vici-> macro or directly by certain built in components and classes. It is responsible for the flow
* of logic in the engine and contains the list of currently loaded game objects
* Status (very much on going)
*/

class CORE_API Vici : public Singleton<Vici>
{

private:

	bool bStarted;	/**< Flag to specify if the engine has run its initilization phase */

	Platform PlatformInstance;	/**< The singleton class for platform functions - access via _Platform-> Macro */
	
	Input InputInstance;	/**< Class for input - Singleton class accessed via the _Input macro */

	GameObjectList GameObjects; /**< List of game objects in the scene */
public:

	/**
	* Engine constructor 
	*/
	Vici();

	/** 
	* Engine destructor 
	*/
	~Vici();

	/**
	* Called once by main - this should be the first call to any Vici function
	* it will run the initilization phase of the engine 
	*/
	void Init();

	/**
	* Called once by main - this should be called anytime after Init() and will start 
	* the first scene and set _started to true.
	* It will also call all the required Awake and Start logic functions etc.
	*/
	void Begin();

	/**
	* Called by game loop to update the current scene - must be called once per frame
	*/
	void Update();

	/**
	* Called by game loop to render the current scene 
	*/
	void Render();

	/**
	* Called when the program or game is being ended (closed)
	*/
	void OnExit();
	
	/**
	* Called when application has been put in the background 
	*/
	void OnEnteredBackground();

	/**
	* Called when the application has resumed focus
	*/
	void OnEnteredFocus();

	/**
	 * Creates an empty GameObject and returns it as a shared_ptr (GameObjectPtr)
	 * Object will also be appended to GameObjects list
	 * @return Shared pointer to GameObject
	 */
	GameObjectPtr CreateGameObject();

	/**
	* Releases the object from the list
	* @return true if item is removed
	*/
	bool ReleaseGameObject(GameObjectPtr gameObject);

	/**
	 * Saves the current GameObject list state to the given file
	 * @param fname The file to be written to
	 * @return returns true if save succedded
	 */
	bool SerializeState(const char* fname);

	/**
	* Deserializes the given engine component with
	* the specified data.
	* @param datafile The runtime relevant path to data
	* @return Returns the deserialized class - will be NULL on failure
	*/
	template<typename T>
	T* DeserializeEngineComponent(const char* datafile)
	{
		std::string fullpath = datafile;
		_Platform->GetFullPath(fullpath);

		// Create the input stream
		CreateInputArchive(arch, inputStream, fullpath);
		T* ret = new T();

		try
		{
			_SERIALIZE_VAR_NAME(*ret,"Data", arch);
		}
		catch (int e)
		{
			delete(ret);
			return NULL;
		}

		return ret;
	}

	/**
	* serializes the given engine component to the output path
	* the path is relative to the running directory
	* @param instance Pointer to the component to serialize
	* @param datafile The runtime relevant path to data
	* @return Returns true on successful serialization
	*/
	template<typename T>
	bool SerializeEngineComponent(T* instance, const char* datafile)
	{
		std::string fullpath = datafile;
		_Platform->GetFullPath(fullpath);

		// Create the input stream
		CreateOutputArchive(arch, outputStream, fullpath);

		try
		{
			_SERIALIZE_VAR_NAME(*instance, "Data", arch);
		}
		catch (int e)
		{
			return false;
		}

		return true;
	}
};

#endif