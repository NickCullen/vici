#ifndef VICI_H
#define VICI_H

/* Length of buffers */
const int BUFF_LEN = 512;

/* Forward decl */
class GameObject;
class VCamera;

/* Required Includes */
#include "tds.h"
#include "GameObjectTree.h"


/* Singleton Classes */
#include "AssetLoader.h"
#include "SceneLoader.h"
#include "LayerSystem.h"
#include "Display.h"
#include "Input.h"
#include "VTime.h"
#include "Logger.h"

/* Macros for vici access and some singleton classes */
#define _Vici Singleton<Vici>::Instance()
#define _Assets Singleton<AssetLoader>::Instance()
#define _SceneLoader Singleton<SceneLoader>::Instance()
#define _Layers Singleton<LayerSystem>::Instance()
#define _Display Singleton<Display>::Instance()
#define _Input Singleton<Input>::Instance()
#define _Time Singleton<VTime>::Instance()
#define _Logger Singleton<Logger>::Instance()

/**
* The core of the engine - A singelton class that can be accessed by anything via the 
* _Vici-> macro or directly by certain built in components and classes. It is responsible for the flow
* of logic in the engine and contains the list of currently loaded game objects
* Status (very much on going)
*/

class Vici : public Singleton<Vici>
{
	friend class SceneLoader;
	friend class VCamera;
private:
	GameObjectTree _objects; /**< Tree of Game Objects in the current scene*/

	TList<VCamera*> _cameras;	/**< List containing all active cameras */

	bool _started;	/**< Flag to specify if the engine has run its initilization phase */

	char _cwd[BUFF_LEN]; /**< Contains the current working directory of the program */

	AssetLoader _asset_loader; /**< The asset Loader for maintaining assets throughout scenes  - Singleton class accessed via the _Assets macro */

	SceneLoader _scene_loader; /**< The scene loader - Singleton class accessed via the _SceneLoader macro */

	LayerSystem _layer_system; /**< Class responsible for loading and maintaining layers - Singleton class accessed via the _Layers macro */

	Display _display;	/**< Class responsible for window presentation and sizes etc. - Singleton class accessed via the _Display macro */

	Input _input;	/**< Class for input - Singleton class accessed via the _Input macro */

	VTime _time;	/**< Class representing time - Singleton class accessed via the _Time macro */
	
	Logger _logger;	/**< Class used for logging strings in debug model - Singleton class accessed via the _Logger macro */
	
	/**
	* Called to register all components of the engine by setting their static
	* reg member variables with the ComponentRegister<T> class (See ComponentFactory.h)
	*/
	void RegisterComponents();
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
	* Temporary convenience method just to quickly add a game object for testing
	* will be removed when things become more solid
	* @param go pointer to the game object to add to the list
	*/
	void AddGameObject(GameObject* go);

	/**
	* Removes the game object from the update list
	* @param go The game object to remove from list
	*/
	void RemoveGameObject(GameObject* go);

	/**
	* Returns the current working directory - note that classes calling this function
	* should not attempt to delete or modify this pointer
	* @return A char pointer (C String) containing the current working directory
	*/
	inline char* GetCwd() { return _cwd; }

	/**
	* Called when application has been put in the background 
	*/
	void OnEnteredBackground();

	/**
	* Called when the application has resumed focus
	*/
	void OnEnteredFocus();
};

#endif