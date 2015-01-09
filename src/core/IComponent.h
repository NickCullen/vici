#ifndef V_COMPONENT
#define V_COMPONENT

/*include the core engine */
#include "core.h"

/*Useful short hand macros*/
#define _transform _go->GetTransform()

class IComponent
{
	/*friend classes to internal objects*/
	friend class Vici;
	friend class GameObject;
private:

protected:
	/*The game object this component belongs to*/
	GameObject* _go;


public:
	IComponent();
	virtual ~IComponent();

	//initialize this component
	virtual void Init(GameObject* go, rapidxml::xml_node<char>* data);

	//functions
	virtual void Awake(){};
	virtual void Start(){}; 
	virtual void Update(){};
	virtual void OnEnable(){};
	virtual void OnDisable(){};
	
	/*registers for a callback*/
	void RegisterCallback(EComponentCallback callback);

	/*Getters and setters*/
	inline GameObject* GetGameObject()
	{
		return _go;
	}
};

#endif