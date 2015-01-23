#include "GameObject.h"
#include "IComponent.h"
#include "ComponentFactory.h"
#include "Transform.h"
#include "IDrawable.h"
#include "MatrixStack.h"

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
			_components.PushBack(component);

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
			_children.PushBack(go);

			//get next
			cur_object = cur_object->next_sibling();
		}
	}
}

void GameObject::ApplyModelMatrix(MatrixStack* stack)
{
	stack->ApplyMatrix(_t->GetModelMatrix());
}

void GameObject::PreRender(OpenGLRenderer* renderer)
{
	TLIST_foreach(IDrawable*, drw, _render_list)
	{
		drw->PreRender(renderer);
	}

	//the matrix stack
	MatrixStack* ms = renderer->GetMatrixStack();

	//apply to child objects
	TLIST_foreach(GameObject*, child, _children)
	{
		//push
		ms->PushMatrix();

		//apply
		child->ApplyModelMatrix(ms);

		//render
		child->PreRender(renderer);

		//pop
		ms->PopMatrix();
	}
}
void GameObject::Render(OpenGLRenderer* renderer)
{
	TLIST_foreach(IDrawable*, drw, _render_list)
	{
		drw->OnRender(renderer);
	}

	//the matrix stack
	MatrixStack* ms = renderer->GetMatrixStack();

	//apply to child objects
	TLIST_foreach(GameObject*, child, _children)
	{
		//push
		ms->PushMatrix();

		//apply
		child->ApplyModelMatrix(ms);

		//render
		child->Render(renderer);

		//pop
		ms->PopMatrix();
	}
}
void GameObject::PostRender(OpenGLRenderer* renderer)
{
	TLIST_foreach(IDrawable*, drw, _render_list)
	{
		drw->PostRender(renderer);
	}

	//the matrix stack
	MatrixStack* ms = renderer->GetMatrixStack();

	//apply to child objects
	TLIST_foreach(GameObject*, child, _children)
	{
		//push
		ms->PushMatrix();

		//apply
		child->ApplyModelMatrix(ms);

		//render
		child->PostRender(renderer);

		//pop
		ms->PopMatrix();
	}
}

void GameObject::RegisterCallback(EComponentCallback type, Delegate callback)
{
	_calls[type].PushBack(callback);
}


void GameObject::SetEnabled(bool flag)
{
	if (flag != _enabled)
	{
		_enabled = flag;
		if (_enabled)
			Dispatch(eOnEnable);
		else
			Dispatch(eOnDisable);

		//dispatch children calls
		TLIST_foreach(GameObject*,obj,_children)
		{
			obj->SetEnabled(flag);
		}
	}
	
}

void GameObject::Dispatch(EComponentCallback method)
{
	TLIST_foreach(Delegate, callback, _calls[method])
	{
		//callback is actually an iterator so we need to
		//dereference it first
		(*callback)();
	}

	//dispatch children calls
	TLIST_foreach(GameObject*, obj, _children)
	{
		obj->Dispatch(method);
	}
}