#ifndef V_GAMEOBJECT
#define V_GAMEOBJECT

#include <vector>
#include "Object.h"
#include "VHash.h"
#include "rapidxml\rapidxml.hpp"

/*Forward Decls*/
class OpenGLRenderer;
class IComponent;
class Transform;

//functions to be called
enum EComponentCallback { Awake, Start, Update, PreRender, OnRender, PostRender, OnEnable, OnDisable, MAX_CALL_COUNT};

class GameObject : public Object
{
private:
	//the transform of this game object
	Transform* _t;

	//the id of this game object
	VHash _id;

	//the list of components
	std::vector<IComponent*> _components;

	//callbacks
	std::vector<IComponent*> _calls[MAX_CALL_COUNT];

	//enabled flag
	bool _enabled;

	//the layer this object is on
	unsigned int _layer;

	//parent GameObject (can be NULL)
	GameObject* _parent;

	//list of child nodes
	std::vector<GameObject*> _children;

protected:

public:
	GameObject();
	~GameObject();

	//initializes the game object
	void Init(GameObject* parent, rapidxml::xml_node<>* node);

	//logic and render funcs
	void Awake();
	void Start();
	void Update();
	void PreRender(OpenGLRenderer* renderer);
	void Render(OpenGLRenderer* renderer);
	void PostRender(OpenGLRenderer* renderer);
	void OnEnable();
	void OnDisable();

	//registers for a callback
	void RegisterCallback(IComponent* comp, EComponentCallback callback);

	/*Get setters - inlined functions are written in header 
	* due to the nature of inline functions*/
	void SetEnabled(bool flag);
	inline bool GetEnabled()
	{
		return _enabled;
	}

	inline unsigned int GetLayer()
	{
		return _layer;
	}

	inline Transform* GetTransform()
	{
		return _t;
	}
};

#endif