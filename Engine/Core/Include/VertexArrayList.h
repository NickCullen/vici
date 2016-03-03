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
	struct VAOInstance
	{
		VAO_t VAO;	// The GL reference to the vertex array
		int32 Context;	// The ID of the context this VAO has been set for
	};

private:

	VAOInstance VAO[MAX_RENDER_CONTEXTS];	// 1 VAO per render contexts

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
	 * Sets the handler for this object
	 */
	void SetHandler(IVertexArrayHandler* handler) { Handler = handler; }
};