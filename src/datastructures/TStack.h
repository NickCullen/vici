#ifndef V_TStack
#define V_TStack

#ifndef NULL
#define NULL 0
#endif

template<typename C>
struct TStackNode
{
	C* _data;
	TStackNode* _next;
	TStackNode* _prev;
};

template<typename C>
class TStack
{
private:
	TStackNode<C>* _head;
	TStackNode<C>* _top;
	int _count;
public:
	TStack(void);
	~TStack(void);

	void Push(C* data);
	C* Pop(void);
	C* Peak(void);

	void Empty(void);
	bool IsEmpty(void);


	/*this function should not be used - it is very slow and only here for testing purposes*/
	C* operator[](int index);
};

template<typename C>
TStack<C>::TStack(void)
{
	_head = NULL;
	_top = NULL;
	_count = 0;
}

template<typename C>
TStack<C>::~TStack(void)
{
	Empty();
}

template<typename C>
bool TStack<C>::IsEmpty(void)
{
	return !_head ? true : false;
}

template<typename C>
C* TStack<C>::Pop(void)
{
	C* retval = NULL;
	if (_top != NULL)
	{
		retval = _top->_data;
		//if we are not on the _head of the TStack
		if (_top->_prev != NULL)
		{
			TStackNode<C>* holder = _top;
			_top = _top->_prev;
			_top->_next = NULL;
			delete(holder);
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

	return retval;
}
template<typename C>
void TStack<C>::Empty(void)
{
	while (Pop())
		;
}
template<typename C>
C* TStack<C>::Peak(void)
{
	if (_top)
	{
		return _top->_data;
	}

	return NULL;
}

template<typename C>
void TStack<C>::Push(C* data)
{
	//if _head has not been set
	if (!_head)
	{
		//set the _top
		_head = new TStackNode<C>();
		_head->_next = NULL;
		_head->_prev = NULL;
		_head->_data = data;
		//set the current to always point to the _top
		_top = _head;
	}
	else
	{
		_top->_next = new TStackNode<C>();
		_top->_next->_prev = _top;
		_top = _top->_next;
		_top->_data = data;
	}

	_count++;
}


//NEVER USE THIS FUNCTION IT IS NASTY I ONLY IMPLEMENTED IT TO TEST FOR DUPLICATED PROCS WHILST ITERATING THROUGH TREE!!!!
template<typename C>
C* TStack<C>::operator[](int index)
{
	TStackNode<C>* tmp = _head;
	int count = 0;
	while (count < index && tmp)
	{
		tmp = tmp->_next;
		count++;
	}
	if (tmp)
		return tmp->_data;
	else
		return NULL;
}

#endif