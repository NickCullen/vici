#ifndef V_GAMEOBJECT_TREE
#define V_GAMEOBJECT_TREE

/* Forward Decl */
class GameObject;

#include "TTree.h"
#include "TList.h"

/**
* Create a tree fromm the TTree so we can have a safe
* Game Object tree in the engine
*/

class GameObjectTree : public TTree<GameObject*>
{
private:
	bool _lock; /**< Used to lock the tree when doing update loop */

	TList<GameObject*> _delete_list; /**< If the list is locked and a game object is trying to be removed then it will be added to this list and removed when list is unlocked */
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
	* Lock the tree
	*/
	void Lock();

	/**
	* Unlock the tree - will remove items in _delete_list if there are any
	*/
	void Unlock();


};
#endif