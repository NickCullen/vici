#ifndef V_TLIST_ITER
#define V_TLIST_ITER

#include "TList.h"

//macro for iterating over a TList like a foreach loop
#define TLIST_foreach(Type, instance, inlist) for (TListIter<Type> instance = TListIter<Type>(&inlist); !instance.IsFinished(); instance++)

template<typename C>
class TListIter
{
private:
	TListNode<C>* _cur_node;
public:
	TListIter(TList<C>*);
	~TListIter(void);

	//post fix
	TListIter<C>& operator++(int);
	//prefix
	TListIter<C>& operator++(void);
	//cast operator
	operator C*()
	{
		return _cur_node->_data;
	}

	C* operator->(void);
	bool IsFinished(void);
};

template <typename C>
TListIter<C>::TListIter(TList<C>* list)
{
	_cur_node = list->Head();
}

template <typename C>
TListIter<C>::~TListIter(void)
{
}

//post fix
template <typename C>
TListIter<C>& TListIter<C>::operator++(int)
{
	if(_cur_node)
	{
		_cur_node = _cur_node->_next;
	}

	return *this;
}
//prefix
template <typename C>
TListIter<C>& TListIter<C>::operator++(void)
{
	if(_cur_node)
	{
		if(_cur_node->_next)
		{
			_cur_node = _cur_node->_next;
		}
	}

	return *this;
}

template <typename C>
C* TListIter<C>::operator->(void)
{
	return _cur_node->_data;
}

template <typename C>
bool TListIter<C>::IsFinished(void)
{
	return !_cur_node ? true : false;
}

#endif