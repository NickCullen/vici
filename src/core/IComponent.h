#ifndef V_COMPONENT
#define V_COMPONENT

//so we can create and register components
#include "core.h"

class IComponent
{
private:

protected:
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

	/*Helper Functions*/
	GameObject* GetGameObject();
};

#endif