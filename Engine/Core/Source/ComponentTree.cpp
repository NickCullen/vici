#include "ComponentTree.h"
#include "IComponent.h"
#include "VHash.h"

/**
* Default ctor
*/
ComponentTree::ComponentTree()
{
	_lock = 0;

	//set comparison function
	SetComparisonFunc(CompareComponent);
}

/**
* Default dtor
*/
ComponentTree::~ComponentTree()
{
	TTree<IComponent*>::~TTree();
}


int ComponentTree::CompareComponent(IComponent* lhs, IComponent* rhs)
{
	if (lhs->ID() < rhs->ID()) return -1;
	else if (lhs->ID() > rhs->ID()) return 1;
	else return 0;
}

int ComponentTree::SearchFunction(VHash id, IComponent* comp)
{
	if (id < comp->ID()) return -1;
	else if (id > comp->ID()) return 1;
	else return 0;
}

/**
* Lock the tree
*/
void ComponentTree::Lock()
{
	_lock++;
}

/**
* Unlock the tree - will remove items in _delete_list if there are any
*/
void ComponentTree::Unlock()
{
	//if locked
	if (_lock > 0)
	{
		//deduct one
		_lock--;

		//if it has become unlocked remove the objects
		if (_lock == 0)
		{
			IComponent* comp = NULL;
			while (!_delete_list.IsEmpty())
			{
				comp = _delete_list.PopBack();
				TTree<IComponent*>::Remove(comp);
				delete(comp);
			}
		}
	}
}

/**
* Override the delete method
* @param comp The component to delete
*/
void ComponentTree::Remove(IComponent* comp)
{
	//if locked buffer the object to remove
	//once the tree becomes unlocked
	if (_lock > 0)
	{
		//set as garbage so we signal that we are deleting it
		comp->SetGarbage();
		//add it to delete list
		_delete_list.PushBack(comp);
	}
	//else just remove
	else
		TTree<IComponent*>::Remove(comp);
}

/**
* Override the delete method for iterator
* @param itr The current iterator
*/
void ComponentTree::Remove(TTreeIter<IComponent*>& itr)
{
	IComponent* comp = (*itr);
	if (comp != NULL)
	{
		Remove(comp);
	}
}

/**
* Called to find the component given the type if
* @param type_id The id of the component (the class name
* in string form
*/
IComponent* ComponentTree::FindComponent(VHash type_id)
{
	return TTree::Find<VHash>(type_id, SearchFunction);
}