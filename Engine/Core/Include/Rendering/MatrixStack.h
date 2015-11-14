#ifndef V_MATRIX_STACK
#define V_MATRIX_STACK

#include "TStack.h"
#include "glm.h"
#include "Core_API.h"

/** 
* Node to place on the matrix stack containing the current snapshot of the 
* matrix at this time 
*/

struct CORE_API MatrixTransform
{
	glm::mat4x4 _current_transform;
};

/**
* This class is reused from an older project it may not last in Vici 
* But I won't find out if I need it or not until I start working on 
* transforms etc. so as for now Status(New - incomplete - maybe deleted).
* No comments to follow
*/

class CORE_API MatrixStack
{
	friend class Renderer;
private:
	TStack<MatrixTransform*> _stack;
	MatrixTransform* _current_matrix;

	glm::mat4x4 _view_matrix;
	glm::mat4x4 _projection_matrix;

	
public:
	MatrixStack(void);
	~MatrixStack(void);

	inline void PushMatrix(void)
	{
		//create the current matrix
		MatrixTransform* tmp = new MatrixTransform();
		//make it a copy
		if (_current_matrix)
			*tmp = *_current_matrix;
		_current_matrix = tmp;
		//add it to the stack
		_stack.Push(_current_matrix);

#ifdef VICI_DEBUG
		//if about 50 then maybe you are not popping?
		if (_stack.Count() >= 50)
		{
			_Platform->LogString("Matrix stack is greater than 50 - Are you sure you haven't left out a matrixstack.pop()?\n");
		}
#endif
	}
	inline void PopMatrix(void)
	{
		//pop the current matrix and get the previous one
		MatrixTransform* tmp = _stack.Peek();
		_stack.Pop();
		delete(tmp);
		_current_matrix = _stack.Peek();
	}

	void ApplyMatrix(const glm::mat4x4& matrix)
	{
		_current_matrix->_current_transform = _current_matrix->_current_transform * matrix;
	}

	inline void Identity(void)
	{
		//set the current matrix to the identity
		MatrixTransform* tmp = _stack.Peek();
		tmp->_current_transform = glm::mat4x4(1.0f, 0.0f, 0.0f, 0.0f,
											0.0f, 1.0f, 0.0f, 0.0f,
											0.0f, 0.0f, 1.0f, 0.0f,
											0.0f, 0.0f, 0.0f, 1.0f);
	}

	inline void SetProjection(glm::mat4x4& projection_mat)
	{
		_projection_matrix = projection_mat;
	}

	inline void SetView(glm::mat4x4& view_mat)
	{
		_view_matrix = view_mat;
	}
};


#endif