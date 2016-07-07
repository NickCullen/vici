#pragma once

#include "PIL/PILAPI.h"
#include "PIL/DataTypes/PlatformTypes.h"
#include "PIL/Graphics/GraphicsTypes.h"

// Non-public abi
struct VBOHandle;


/** 
 * Base class for Vertex and Index buffers
 */
class PIL_API VBuffer
{
protected:
	void* Data;			/*<< Buffer data in memory */

	int32 Count;		/**< Number of items in this buffer object */

	int32 Size;			/**< Current size (in bytes) of the buffer data */

	int32 MaxSize;		/**< Allocated size (in bytes) of Data */

	VBOHandle* VBO;		/**< Graphics API specific Handle to the vertex buffer on the GPU*/

	EBufferType Type;	/**< The type of this vertex buffer */

	EBufferUse Usage;	/**< How this buffer is to be used */

	/**
	 * Resizes the Data array to NewSize where NewSize is the size (in bytes) of new array
	 * @param NewSize Size (in bytes) of the buffer
	 */
	void Resize(int32 NewSize);

	/**
	 * Classes deriving from VBuffer must implement 
	 * GetSingleItemDataSize which should return the size of
	 * 1 element in the Data array. This would be the size of a vertex
	 * in a vertex buffer or the size of 1 index element in an IndexBuffer
	 * Internal use only.
	 * @return Size (in bytes) of a SINGLE element in the buffer
	 */
	virtual int32 GetSingleItemDataSize() = 0;

	/**
	 * Sets the size of a single element in the buffer
	 * @param size Size (in bytes) of a single element in the buffer
	 */
	virtual void SetSingleItemDataSize(int32 size) = 0;
public:

	/**
	 * Overloaded constructor
	 * @param type The buffer type (See EBufferType)
	 * @param usage How this buffer is to be used (See EBufferUse)
	 */
	VBuffer(EBufferType type, EBufferUse usage);

	/**
	 * Default destructor
	 */
	virtual ~VBuffer();

	/**
	 * Binds the buffer on the GPU
	 */
	void Bind();

	/**
	 * Creates the VBO and prepares for uploading data to the gpu
	 */
	bool Lock();

	/**
	 * Sends the data upto the GPU
	 */
	void Unlock();

	/**
	 * Frees the data held in client (RAM) memory
	 */
	void FlushClientMemory();

	/**
	 * Frees the data held on the GPU
	 */
	void FlushGPUMemory();

	/**
	 * Free both client and GPU memory
	 */
	void Flush();

	/**
	 * Returns the number of elements in the buffer
	 */
	inline int32 GetCount() { return Count; }

	/**
	 * Creates the buffer from a c-style array
	 * @param data Pointer to the data
	 * @param sizeOfArray The size of array (in bytes) 
	 * @param sizePerEntry The size of a single element in the data array. This is size per vertex in a vertex buffer or a single index element in an index buffer
	 */
	void FromArray(void* data, int32 sizeOfArray, int32 sizePerEntry);
};