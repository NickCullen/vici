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
	_start_called = false;
}
GameObject::~GameObject()
{

}

void GameObject::Init(GameObject* parent, XmlNode& node)
{
	//set parent
	_parent = parent;

	if (!node.IsNull())
	{
		/*set initial vars*/
		_hash = node.GetAttributeString("id");
		if (node.GetAttributeBool("indestructable")) MakeIndestructable();
		_enabled = node.GetAttributeBool("enabled");
		_layer = node.GetAttributeBool("layer");

		/* If there is a transform node init the transform */
		XmlNode transform = node.GetChild("transform");
		if (!transform.IsNull())
		{
			_t->Init(transform);
		}

		/*Create components*/
		XmlNode cur_component = node.GetChild("component");
		while (!cur_component.IsNull())
		{
			//create the component
			IComponent* component = ComponentFactory::CreateComponent(cur_component.GetAttributeString("type"));

			//set its game object
			component->SetGameObject(this);

			//init the component from xml
			component->Init(cur_component);

			//add it to the components list
			_components.Insert(component);

			//get next
			cur_component = cur_component.NextSibling("component");
		}

		/* create sub objects*/
		XmlNode cur_object = node.GetChild("gameobject");
		while (!cur_object.IsNull())
		{
			GameObject* go = new GameObject();

			//init this object
			go->Init(this, cur_object);

			//add to child node
			_children.Insert(go);

			//get next
			cur_object = cur_object.NextSibling("gameobject");
		}
	}
}

void GameObject::OnDestroy()
{
	//if this is the top most parent remove from update list
	if (_parent == NULL)
		_Vici->RemoveGameObject(this);
	//else remove from parents _children list
	else
		_parent->_children.Remove(this);

	_components.Lock();
	//destroy components
	TTREE_foreach(IComponent*, comp, _components)
	{
		//destroy it
		Destroy(comp);
	}
	_components.Unlock();

	//clear render lists
	_render_list.Empty();

	//clear calls
	for (int i = 0; i < eMAX_CALL_COUNT; i++)
	{
		_calls[i].Empty();
	}

	//delete transform
	delete(_t);

	_children.Lock();
	//destroy children
	TTREE_foreach(GameObject*, child, _children)
	{
		Destroy(child);
	}
	_children.Unlock();
}


void GameObject::AddComponent(IComponent* comp)
{
	_components.Insert(comp);
}

void GameObject::RemoveComponent(IComponent* comp)
{
	_components.Remove(comp);
}

IComponent* GameObject::FindComponent(VHash type_id)
{
	return _components.FindComponent(type_id);
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
	TTREE_foreach(GameObject*, child, _children)
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
	TTREE_foreach(GameObject*, child, _children)
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
	TTREE_foreach(GameObject*, child, _children)
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
		TTREE_foreach(GameObject*, obj, _children)
		{
			obj->SetEnabled(flag);
		}
	}
	
}

void GameObject::Dispatch(EComponentCallback method)
{
	//make sure to lock components
	_components.Lock();

	TLIST_foreach(Delegate, callback, _calls[method])
	{
		//callback is actually an iterator so we need to
		//dereference it first
		(*callback)();

		//if this object has been set to garbage break out
		if (IsGarbage())
		{
			//unlock components
			_components.Unlock();

			//return
			return;
		}
	}

	//unlock components
	_components.Unlock();

	_children.Lock();

	//dispatch children calls
	TTREE_foreach(GameObject*, obj, _children)
	{
		if(!obj->IsGarbage()) obj->Dispatch(method);
	}

	_children.Unlock();
}

void GameObject::OnStart()
{
	//if already called return
	if (_start_called) return;

	//else set true and carry on
	_start_called = true;

	//make sure to lock components
	_components.Lock();

	TTREE_foreach(IComponent*, comp, _components)
	{
		comp->OnStart();

		//if this object has been set to garbage break out
		if (IsGarbage())
		{
			//unlock components
			_components.Unlock();

			//return
			return;
		}
	}

	//unlock components
	_components.Unlock();

	_children.Lock();

	//dispatch children calls
	TTREE_foreach(GameObject*, obj, _children)
	{
		if (!obj->IsGarbage()) obj->OnStart();
	}

	_children.Unlock();

}