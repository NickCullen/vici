#pragma once

#include "PIL/PILAPI.h"
#include "PIL/DataTypes/PlatformTypes.h"
#include "GraphicsConstants.h"
#include "PIL/Collections/String.h"

// non-public abi
struct VAOHandle;

/**
 * Objects that manage Vertex array lists must
 * implement a VertexArrayHandler interface
 */
class PIL_API IVertexArrayHandler
{
public:
	virtual bool BindArrays(const class VVertexArrayList& list) = 0;
};

/**
 * Class used to manage sending vertex arrays to the shader
 * The idea is to create a vertex buffer and bind each element
 * to an array entry. This requires access to the shader that will
 * use these arrays as input
 */
class PIL_API VVertexArrayList
{
private:
	VAOHandle* VAO[MAX_RENDER_CONTEXTS];	// 1 VAO per render context

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
	* it will call the handler bind array func so the user
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
	* Binds the VAO and calls the handler BindArray function
	* even if the VAO already has arrays bound to it
	*/
	void BindForceNotify();

	/** 
	 * Sets the handler for this object
	 */
	inline void SetHandler(IVertexArrayHandler* handler) { Handler = handler; }
};