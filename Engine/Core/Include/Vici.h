#ifndef VICI_H
#define VICI_H

/* Forward decl */
class GameObject;

/* Required Includes */
#include "CoreAPI.h"
#include "Singleton.h"

#include "Platform.h"
#include "Input.h"

/* Macros for vici access and some singleton classes */
#define _Vici Singleton<Vici>::Instance()

/**
* The core of the engine - A singelton class that can be accessed by anything via the 
* _Vici-> macro or directly by certain built in components and classes. It is responsible for the flow
* of logic in the engine and contains the list of currently loaded game objects
* Status (very much on going)
*/

class CORE_API Vici : public Singleton<Vici>
{

private:

	bool _started;	/**< Flag to specify if the engine has run its initilization phase */

	Platform _platform;	/**< The singleton class for platform functions - access via _Platform-> Macro */
	
	Input _input;	/**< Class for input - Singleton class accessed via the _Input macro */

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
	* Called when application has been put in the background 
	*/
	void OnEnteredBackground();

	/**
	* Called when the application has resumed focus
	*/
	void OnEnteredFocus();

};

#endif