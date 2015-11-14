#ifndef V_GAMEOBJECT_TREE
#define V_GAMEOBJECT_TREE

/* Forward Decl */
class GameObject;

#include "PlatformDefinitions.h"
#include "CoreAPI.h"
#include "TTree.h"
#include "TList.h"

/**
* Create a tree fromm the TTree so we can have a safe
* Game Object tree in the engine
*/

class CORE_API GameObjectTree : public TTree<GameObject*>
{
private:
	int32 _lock; /**< Counter for locking the object list*/

	TList<GameObject*> _delete_list; /**< If the list is locked and a game object is trying to be removed then it will be added to this list and removed when list is unlocked */

	/**
	* Callback function for tree search
	* @param lhs The left hand side of search
	* @param rhs The Right Hand side of search
	* @return -1 if lhs < rhs, 0 if lhs == rhs, 1 if lhs > rhs
	*/
	static int32 CompareGameObject(GameObject* lhs, GameObject* rhs);

public:
	/**
	* Default ctor
	*/
	GameObjectTree();

	/**
	* Default dtor
	*/
	~GameObjectTree();

	/**
	* Lock the tree (adds one to _lock)
	*/
	void Lock();

	/**
	* Unlock the tree - will remove items in _delete_list if there are any
	* Will detuct 1 from _lock
	*/
	void Unlock();

	/**
	* Override the delete method 
	* @param go The GameObject to delete
	*/
	void Remove(GameObject* go);

	/**
	* Override the delete method for iterator
	* @param itr The current iterator
	*/
	void Remove(TTreeIter<GameObject*>& itr);
};
#endif