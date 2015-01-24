#include "GameObjectTree.h"
#include "GameObject.h"
#include "VHash.h"

/**
* Default ctor
*/
GameObjectTree::GameObjectTree()
{
	_lock = 0;

	//set comparison function
	SetComparisonFunc(CompareGameObject);
}

/**
* Default dtor
*/
GameObjectTree::~GameObjectTree()
{
	TTree<GameObject*>::~TTree();
}


int GameObjectTree::CompareGameObject(GameObject* lhs, GameObject* rhs)
{
	if (lhs->ID() < rhs->ID()) return -1;
	else if (lhs->ID() > rhs->ID()) return 1;
	else return 0;
}

/**
* Lock the tree
*/
void GameObjectTree::Lock()
{
	_lock++;
}

/**
* Unlock the tree - will remove items in _delete_list if there are any
*/
void GameObjectTree::Unlock()
{
	//if locked
	if (_lock > 0)
	{
		//deduct one
		_lock--;

		//if it has become unlocked remove the objects
		if (_lock == 0)
		{
			GameObject* go = NULL;
			while (!_delete_list.IsEmpty())
			{
				go = _delete_list.PopBack();
				TTree<GameObject*>::Remove(go);
				delete(go);
			}
		}
	}
}

/**
* Override the delete method
* @param go The GameObject to delete
*/
void GameObjectTree::Remove(GameObject* go)
{
	//if locked buffer the object to remove
	//once the tree becomes unlocked
	if (_lock > 0)
	{
		//set as garbage so we signal that we are deleting it
		go->SetGarbage();
		//add it to delete list
		_delete_list.PushBack(go);
	}
	//else just remove
	else
		TTree<GameObject*>::Remove(go);
}

/**
* Override the delete method for iterator
* @param itr The current iterator
*/
void GameObjectTree::Remove(TTreeIter<GameObject*>& itr)
{
	GameObject* go = (*itr);
	if (go != NULL)
	{
		Remove(go);
	}
}