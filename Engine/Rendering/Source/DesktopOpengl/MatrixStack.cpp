#include "MatrixStack.h"

MatrixStack::MatrixStack(void)
{
	//init vars
	_current_matrix = NULL;
	PushMatrix();
}

MatrixStack::~MatrixStack(void)
{
	while (!_stack.IsEmpty())
	{
		_current_matrix = _stack.Pop();
		delete(_current_matrix);
	}
}