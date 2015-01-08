#include "GameObject.h"
#include "IComponent.h"
#include "IDrawable.h"
#include "ComponentFactory.h"
#include "Transform.h"

GameObject::GameObject()
{
	_enabled = true;
	_parent = NULL;
	_layer = 0;	//0 is default layer
	_t = new Transform();
}
GameObject::~GameObject()
{

}

void GameObject::Init(GameObject* parent, rapidxml::xml_node<>* node)
{
	//set parent
	_parent = parent;

	if (node != NULL)
	{
		/*set initial vars*/
		_id = node->first_attribute("id")->value();
		if (atoi(node->first_attribute("indestructable")->value()) == 1) MakeIndestructable();
		_enabled = (atoi(node->first_attribute("enabled")->value()) == 1) ? true : false;
		_layer = atoi(node->first_attribute("layer")->value());

		/*Create components*/
		rapidxml::xml_node<char>* cur_component = node->first_node("components")->first_node("component");
		while (cur_component)
		{
			//create the component
			IComponent* component = ComponentFactory::CreateComponent(cur_component->first_attribute("type")->value());

			//init the component
			component->Init(this, cur_component);

			//add it to the components list
			_components.push_back(component);

			//get next
			cur_component = cur_component->next_sibling();
		}

		/* create sub objects*/
		rapidxml::xml_node<char>* cur_object = node->first_node("gameobjects")->first_node("gameobject");
		while (cur_object)
		{
			GameObject* go = new GameObject();

			//init this object
			go->Init(this, cur_object);

			//add to child node
			_children.push_back(go);

			//get next
			cur_object = cur_object->next_sibling();
		}
	}
}
//logic and render funcs
void GameObject::Awake()
{
	for (unsigned int i = 0; i < _calls[EComponentCallback::Awake].size(); i++)
	{
		_calls[EComponentCallback::Awake].at(i)->Awake();
	}

	//dispatch children calls
	for (unsigned int i = 0; i < _children.size(); i++)
	{
		_children[i]->Awake();
	}
}
void GameObject::Start()
{
	for (unsigned int i = 0; i < _calls[EComponentCallback::Start].size(); i++)
	{
		_calls[EComponentCallback::Start].at(i)->Start();
	}

	//dispatch children calls
	for (unsigned int i = 0; i < _children.size(); i++)
	{
		_children[i]->Start();
	}
}

void GameObject::Update()
{
	for (unsigned int i = 0; i < _calls[EComponentCallback::Update].size(); i++)
	{
		_calls[EComponentCallback::Update].at(i)->Update();
	}

	//dispatch children calls
	for (unsigned int i = 0; i < _children.size(); i++)
	{
		_children[i]->Update();
	}
}
void GameObject::PreRender(OpenGLRenderer* renderer)
{
	IDrawable* dr = NULL;
	for (unsigned int i = 0; i < _calls[EComponentCallback::PreRender].size(); i++)
	{
		dr = (IDrawable*)_calls[EComponentCallback::PreRender].at(i);
		dr->PreRender(renderer);
	}

	//dispatch children calls
	for (unsigned int i = 0; i < _children.size(); i++)
	{
		_children[i]->PreRender(renderer);
	}
}
void GameObject::Render(OpenGLRenderer* renderer)
{
	IDrawable* dr = NULL;
	for (unsigned int i = 0; i < _calls[EComponentCallback::OnRender].size(); i++)
	{
		dr = (IDrawable*)_calls[EComponentCallback::OnRender].at(i);
		dr->OnRender(renderer);
	}

	//dispatch children calls
	for (unsigned int i = 0; i < _children.size(); i++)
	{
		_children[i]->Render(renderer);
	}
}
void GameObject::PostRender(OpenGLRenderer* renderer)
{
	IDrawable* dr = NULL;
	for (unsigned int i = 0; i < _calls[EComponentCallback::PostRender].size(); i++)
	{
		dr = (IDrawable*)_calls[EComponentCallback::PostRender].at(i);
		dr->PostRender(renderer);
	}

	//dispatch children calls
	for (unsigned int i = 0; i < _children.size(); i++)
	{
		_children[i]->PostRender(renderer);
	}
}

void GameObject::OnEnable()
{
	for (unsigned int i = 0; i < _calls[EComponentCallback::OnEnable].size(); i++)
	{
		_calls[EComponentCallback::OnEnable].at(i)->OnEnable();
	}
	
	//dispatch children calls
	for (unsigned int i = 0; i < _children.size(); i++)
	{
		_children[i]->OnEnable();
	}
}
void GameObject::OnDisable()
{
	for (unsigned int i = 0; i < _calls[EComponentCallback::OnDisable].size(); i++)
	{
		_calls[EComponentCallback::OnDisable].at(i)->OnDisable();
	}

	//dispatch children calls
	for (unsigned int i = 0; i < _children.size(); i++)
	{
		_children[i]->OnDisable();
	}
}
void GameObject::RegisterCallback(IComponent* comp, EComponentCallback callback)
{
	_calls[callback].push_back(comp);
}


void GameObject::SetEnabled(bool flag)
{
	if (flag != _enabled)
	{
		_enabled = flag;
		if (_enabled)
			OnEnable();
		else
			OnDisable();

		//dispatch children calls
		for (unsigned int i = 0; i < _children.size(); i++)
		{
			_children[i]->SetEnabled(flag);
		}
	}
	
}