#ifndef V_COMPONENT_TREE
#define V_COMPONENT_TREE

/* Forward Decl */
class IComponent;

#include "TTree.h"
#include "TList.h"
#include "VHash.h"
#include "CoreAPI.h"
/**
* Tree stored by game objects to store all their
* components and make it easier and more efficent 
* to find and return components
*/

class CORE_API ComponentTree : public TTree<IComponent*>
{
private:
	int32 _lock; /**< Counter for locking the tree*/

	TList<IComponent*> _delete_list; /**< If the list is locked and a commponent is trying to be removed then it will be added to this list and removed when list is unlocked */

	/**
	* Callback function for comparing components
	* @param lhs The left hand side of search
	* @param rhs The Right Hand side of search
	* @return -1 if lhs < rhs, 0 if lhs == rhs, 1 if lhs > rhs
	*/
	static int32 CompareComponent(IComponent* lhs, IComponent* rhs);

	/**
	* Callback function for tree search
	* @param id The typename of the component
	* @param rhs The component to check against
	* @return -1 if id < comp, 0 if id == comp, 1 if id > comp
	*/
	static int32 SearchFunction(VHash id, IComponent* comp);

public:
	/**
	* Default ctor
	*/
	ComponentTree();

	/**
	* Default dtor
	*/
	~ComponentTree();

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
	* @param comp The the component to delete
	*/
	void Remove(IComponent* comp);

	/**
	* Override the delete method for iterator
	* @param itr The current iterator
	*/
	void Remove(TTreeIter<IComponent*>& itr);

	/**
	* Called to find the component given the type if
	* @param type_id The id of the component (the class name
	* in string form
	*/
	IComponent* FindComponent(VHash type_id);
};
#endif