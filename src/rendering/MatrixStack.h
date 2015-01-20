#ifndef V_MATRIX_STACK
#define V_MATRIX_STACK

#include "TStack.h"
#include "glm.h"

struct MatrixTransform
{
	glm::mat4x4 _current_transform;
	MatrixTransform(void)
	{
		_current_transform = glm::mat4x4(1.0f, 0.0f, 0.0f, 0.0f,
										0.0f, 1.0f, 0.0f, 0.0f,
										0.0f, 0.0f, 1.0f, 0.0f,
										0.0f, 0.0f, 0.0f, 1.0f);
	}
};

class MatrixStack
{
	friend class VCamera;
	friend class OpenGLRenderer;
private:
	TStack<MatrixTransform*> _stack;
	MatrixTransform* _current_matrix;
public:
	MatrixStack(void);
	~MatrixStack(void);

	__forceinline void PushMatrix(void)
	{
		//create the current matrix
		MatrixTransform* tmp = new MatrixTransform();
		//make it a copy
		if (_current_matrix)
			*tmp = *_current_matrix;
		_current_matrix = tmp;
		//add it to the stack
		_stack.Push(_current_matrix);
	}
	__forceinline void PopMatrix(void)
	{
		//pop the current matrix and get the previous one
		MatrixTransform* tmp = _stack.Peek();
		_stack.Pop();
		delete(tmp);
		_current_matrix = _stack.Peek();
	}

	void ApplyMatrix(glm::mat4x4& matrix)
	{
		_current_matrix->_current_transform = _current_matrix->_current_transform * matrix;
	}

	__forceinline void Identity(void)
	{
		//set the current matrix to the identity
		MatrixTransform* tmp = _stack.Peek();
		tmp->_current_transform = glm::mat4x4(1.0f, 0.0f, 0.0f, 0.0f,
											0.0f, 1.0f, 0.0f, 0.0f,
											0.0f, 0.0f, 1.0f, 0.0f,
											0.0f, 0.0f, 0.0f, 1.0f);
	}
};


#endif