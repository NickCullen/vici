#ifndef V_STACK
#define V_STACK

#ifndef NULL
#define NULL 0
#endif

template<typename C>
struct StackNode
{
	C* data;
	StackNode* nextNode;
	StackNode* prevNode;
};

template<typename C>
class Stack
{
private:
	StackNode<C>* head;
	StackNode<C>* top;
	int nodeCount;
public:
	Stack(void);
	~Stack(void);

	void push(C* data);
	C* pop(void);
	C* peak(void);

	void empty(void);
	bool isEmpty(void);


	/*this function should not be used - it is very slow and only here for testing purposes*/
	C* operator[](int index);
};

template<typename C>
Stack<C>::Stack(void)
{
	head = NULL;
	top = NULL;
	nodeCount = 0;
}

template<typename C>
Stack<C>::~Stack(void)
{
	empty();
}

template<typename C>
bool Stack<C>::isEmpty(void)
{
	return !head ? true : false;
}

template<typename C>
C* Stack<C>::pop(void)
{
	C* retval = NULL;
	if (top != NULL)
	{
		retval = top->data;
		//if we are not on the head of the stack
		if (top->prevNode != NULL)
		{
			StackNode<C>* holder = top;
			top = top->prevNode;
			top->nextNode = NULL;
			delete(holder);
			nodeCount--;
		}
		else
		{
			delete(top);
			top = NULL;
			head = NULL;
			nodeCount--;
		}

	}

	return retval;
}
template<typename C>
void Stack<C>::empty(void)
{
	while (pop())
		;
}
template<typename C>
C* Stack<C>::peak(void)
{
	if (top)
	{
		return top->data;
	}

	return NULL;
}

template<typename C>
void Stack<C>::push(C* data)
{
	//if head has not been set
	if (!head)
	{
		//set the top
		head = new StackNode<C>();
		head->nextNode = NULL;
		head->prevNode = NULL;
		head->data = data;
		//set the current to always point to the top
		top = head;
	}
	else
	{
		top->nextNode = new StackNode<C>();
		top->nextNode->prevNode = top;
		top = top->nextNode;
		top->data = data;
	}

	nodeCount++;
}


//NEVER USE THIS FUNCTION IT IS NASTY I ONLY IMPLEMENTED IT TO TEST FOR DUPLICATED PROCS WHILST ITERATING THROUGH TREE!!!!
template<typename C>
C* Stack<C>::operator[](int index)
{
	StackNode<C>* tmp = head;
	int count = 0;
	while (count < index && tmp)
	{
		tmp = tmp->nextNode;
		count++;
	}
	if (tmp)
		return tmp->data;
	else
		return NULL;
}

#endif