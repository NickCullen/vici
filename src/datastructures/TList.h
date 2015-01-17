#ifndef V_TLIST
#define V_TLIST

template<typename C>
struct TListNode
{
	C* _data;
	TListNode* _next;
	TListNode* _prev;
};


template<typename C>
class TList
{

private:
	TListNode<C>* _head;
	TListNode<C>* _top;
	int _count;
public:
	TList(void);
	~TList(void);

	void Add(C* data);
	bool IsEmpty(void);
	void Empty(void);
	TListNode<C>* Head(void);
	C* operator[](int index);

	int Count(void);

	//deletes node data AND node
	void NukeList(void);
};

template<typename C>
TList<C>::TList(void)
{
	_head = NULL;
	_top = NULL;
	_count = 0;
}

template<typename C>
TList<C>::~TList(void)
{
	Empty();
}
template<typename C>
TListNode<C>* TList<C>::Head(void)
{
	return _head;
}
template<typename C>
int TList<C>::Count(void)
{
	return _count;
}
template<typename C>
bool TList<C>::IsEmpty(void)
{
	return !_head ? true : false;
}

template<typename C>
void TList<C>::Empty(void)
{
	while(!IsEmpty())
	{
		if(_top)
		{
			//if we are not on the _head of the stack
			if(_top->_prev != NULL)
			{
				TListNode<C>* holder = _top;
				_top = _top->_prev;
				_top->_next = NULL;
				delete(holder);
				holder = NULL;
				_count--;
			}
			else
			{
				delete(_top);
				_top = NULL;
				_head = NULL;
				_count--;
			}
		
		}
	}
}
template<typename C>
void TList<C>::Add(C* data)
{
	//if _head has not been set
	if(!_head)
	{
		//set the _top
		_head = new TListNode<C>();
		_head->_next = NULL;
		_head->_prev = NULL;
		_head->_data = data;
		//set the current to always point to the _top
		_top = _head;
	}
	else
	{
		_top->_next = new TListNode<C>();
		_top->_next->_prev = _top;
		_top = _top->_next;
		_top->_data = data;
	}

	_count++;
}

template<typename C>
C* TList<C>::operator[](int index)
{
	TListNode<C>* tmp = _head;
	int count = 0;
	while (count < index && tmp)
	{
		tmp = tmp->_next;
		count++;
	}
	if(tmp)
		return tmp->_data;
	else
		return NULL;
}

template<typename C>
void TList<C>::NukeList(void)
{
	while(!IsEmpty())
	{
		if(_top)
		{
			//if we are not on the _head of the stack
			if(_top->_prev != NULL)
			{
				TListNode<C>* holder = _top;
				_top = _top->_prev;
				_top->_next = NULL;
				delete(holder->data);
				delete(holder);
				_count--;
			}
			else
			{
				delete(_top->data);
				delete(_top);
				_top = NULL;
				_head = NULL;
				_count--;
			}
		
		}
	}
}

#endif