#pragma once

#include "CoreAPI.h"
#include "VTypes.h"
#include "Delegate.h"
#include "EngineConstants.h"

typedef uint32 VAO_t;

/**
 * Objects that manage Vertex array lists must
 * implement a VertexArrayHandler interface
 */
class CORE_API IVertexArrayHandler 
{
public:
	virtual void BindArrays(const class VVertexArrayList& list) = 0;
};

class CORE_API VVertexArrayList
{

private:

	VAO_t VAO[MAX_RENDER_CONTEXTS];	// 1 VAO per render context

	IVertexArrayHandler* Handler;	// Handler for this array;

	/**
	* Checks all VAOS for this VertexArrayList
	* will return true if the gl vao was found in
	* VAO member var
	*/
	bool DoesVAOExist();

	/**
	* Allocate a VAO for this context and notify the user
	* so that they can set the vao data
	*/
	void AllocVAOAndNotify();
public:
	VVertexArrayList();
	VVertexArrayList(IVertexArrayHandler* handler);

	~VVertexArrayList();

	/**
	* Binds the vertex arrays, if the vao has
	* Not been allocated for the current context,
	* it will call the UpdateVertexListDelegate so the user
	* can rebind all the vertex arrays
	*/
	void Bind();

	/**
	* Does the same as Bind but doesn't notify
	* the vertex array handler. This may be useful if 
	* You want to bind the array object and then set up
	* your array data
	*/
	void BindNoNotify();

	/** 
	 * Sets the handler for this object
	 */
	void SetHandler(IVertexArrayHandler* handler) { Handler = handler; }
};