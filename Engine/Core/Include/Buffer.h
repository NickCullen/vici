#pragma once

#include "CoreAPI.h"
#include "VTypes.h"
#include "EngineConstants.h"

// Typedefs
typedef uint32 VBO_t;

// Defines what type of buffer this is
enum EBufferType
{
	ARRAY_BUFFER,			// vertex data
	ELEMENT_BUFFER			// index data
};

// Defines how this buffer is to be used
enum EBufferUse
{
	STATIC_DRAW,		// Upload once - draw many times
	DYNAMIC_DRAW,		// Changed from time to time but drawn many more times than that
	STREAM_DRAW		// Vertex data will change almost every frame
};

/** 
 * Base class for Vertex and Index buffers
 */
class CORE_API VBuffer
{
private:

protected:
	void* Data;		// Buffer data in memory

	int32 Count;	// Number of items in this buffer object

	int32 Size;			// Current size in bytes of the buffer data

	int32 MaxSize;		// Allocated size in bytes of Data

	VBO_t VBO;	// Reference to the vertex buffer in gpu

	EBufferType Type;	// The type of vertex buffer

	EBufferUse Usage;	// How this buffer is to be used

	// Convert Type to its GLEnum equiv.
	uint32 BufferTypeToGL();

	// Convert its usage to its GLenum equiv.
	uint32 BufferUsageToGL();

	// Resizes Data array to NewSize where NewSize = size in bytes of new array
	void Resize(int32 NewSize);

	// Classes deriving from VBuffer must implement 
	// GetSingleItemDataSize which should return the size of
	// 1 element in the Data array. This would be the size of a vertex
	// in a vertex buffer or the size of 1 index element in an IndexBuffer
	// Internal use only.
	virtual int32 GetSingleItemDataSize() = 0;

	// Same reason as GetSingleItemDataSize, except this will
	// force the derived class to set its datasize
	virtual void SetSingleItemDataSize(int32 size) = 0;
public:

	VBuffer(EBufferType type, EBufferUse usage);

	virtual ~VBuffer();

	// Binds the vertex buffer
	void Bind();

	// Creates the VBO and prepares for uploading vertices
	bool Lock();

	// Sends the vertex data upto the GPU
	void Unlock();

	// Frees the data held in client memory
	void FlushClientMemory();

	// Frees the data held on the GPU
	void FlushGPUMemory();

	// Frees all data
	void Flush();

	// Getters
	inline int32 GetCount() { return Count; }

	// Sets the data from an array
	void FromArray(void* data, int32 sizeOfArray, int32 sizePerEntry);
};