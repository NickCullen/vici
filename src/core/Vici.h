#ifndef VICI_H
#define VICI_H

//length of cwd
const int BUFF_LEN = 512;

/*Forward decl */
class GameObject;
class VCamera;

#include "tds.h"

/*Macros for vici access*/
#define _vici Vici::Instance()

/**
* The core of the engine - A singelton class that can be accessed by anything via the 
* _vici-> macro or directly by certain built in components and classes. It is responsible for the flow
* of logic in the engine and contains the last of currently loaded game objects
* Status (very much on going)
*/

class Vici
{
	friend class SceneLoader;
	friend class VCamera;
private:
	static Vici* _instance; /**< The only allowed running instance of the engine */

	TTree<GameObject*> _objects; /**< Tree of Game Objects (soon to turn into a GameObjectTree) */
	TList<VCamera*> _cameras;	/**< List containing all active cameras */

	bool _started;	/**< Flag to specify if the engine has run its initilization phase */

	char _cwd[BUFF_LEN]; /**< Contains the current working directory of the program */

	/**
	* Called to register all components of the engine by setting their static
	* reg member variables with the DerivedRegister<T> class (See ComponentFactory.h)
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
	* will also call all the required Awake and Start logic functions etc.
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
	* Returns the current working directory - note that classes calling this function
	* should not attempt to delete this pointer
	* @return a char pointer containing the current working directory
	*/
	char* GetCwd();

	/**
	* Temporary convenience method just to quickly adda game object for testing
	* will be removed when things become more solid
	* @param go pointer to the game object to add to the list
	*/
	void AddGameObject(GameObject* go);

	/**
	* Static getter to return the running instance of Vici (may be NULL)
	*/
	static inline Vici* Instance()
	{
		return _instance;
	}
};

#endif