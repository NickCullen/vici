#include "MatrixStack.h"

MatrixStack::MatrixStack(void)
{
	//init vars
	_current_matrix = NULL;
	PushMatrix();
}

MatrixStack::~MatrixStack(void)
{

}