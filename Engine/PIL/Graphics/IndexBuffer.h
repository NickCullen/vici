#pragma once

#include "Buffer.h"

/**
 * Buffer which contain indices into a vertex buffer
 */
class PIL_API VIndexBuffer : public VBuffer
{
private:
	EIndexType IndexType;	/**< Type of faces this index buffer draws in */

protected:

	/**
	 * Override method
	 * @return Returns the size (in bytes) of a single index in the array
	 */
	virtual int32 GetSingleItemDataSize() override;

	/**
	* Override method
	* @param size Sets the size of a single index element
	*/
	virtual void SetSingleItemDataSize(int32 size) override;
public:
	/**
	 * Overloaded constructor with default params
	 */
	VIndexBuffer(EIndexType faceType = INDEX_TYPE_TRIANGLES, EBufferUse usage = STATIC_DRAW);

	/**
	 * Default destructor
	 */
	~VIndexBuffer();

	/**
	 * Triggers the drawing of the bound buffers
	 * Using the indicies specified in this buffer
	 */
	void DrawElements();
};