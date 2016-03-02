#pragma once

#include "CoreAPI.h"
#include "VTypes.h"

typedef uint32 VBO_t;

// max number of elements per vertex
static const int MAX_BUFFER_ELEMENTS = 16;

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
 * Class for dynamic vertex buffers - General logic is as follows:
 * 1. Allocate each element per vertex using AddElement
 * 2. Pre-allocate space using AllocateVertices
 * 3. Add a vertex using AddVertex
 * 4. Fill in the currently add vertex using AddData and give in the 
 *    element ID you got from step 1.
 */
class CORE_API VVertexBuffer
{
	// So we can store elements and their sizes
	struct VVertexElement
	{
		int32 Size;				// Sizeof this element
		int32 Offset;			// Offset (in bytes) from the first element
	};

private:
	
	void* Data;	// Vertex data in memory

	VVertexElement Elements[MAX_BUFFER_ELEMENTS];	// Array of elements

	int32 NumOfElements;	// Number of elements in this buffer object

	int32 VertexSize;	// Size per vertex

	int32 Count;		// Number of vertices in this buffer object

	int32 Size;			// Current size in bytes of the buffer data

	int32 MaxSize;		// Allocated size in bytes of Data

	VBO_t VBO;	// Reference to the vertex buffer in gpu

	EBufferType Type;	// The type of vertex buffer

	EBufferUse Usage;	// How this buffer is to be used

	// Converts the Type value to 
	// its respective GLenum
	uint32 BufferTypeToGL();
	uint32 BufferUsageToGL();

	// Resizes Data array to NewSize where NewSize = size in bytes of new array
	void Resize(int32 NewSize);
public:
	VVertexBuffer(EBufferType type = ARRAY_BUFFER, EBufferUse useage = STATIC_DRAW);
	~VVertexBuffer();

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

	// Allocate space for specified number of vertices
	// Allocates data array to be VertexSize * Count
	void AllocateVertices(int32 Count);

	// Adds an element and returns the id of it
	template<typename T>
	int AddElement()
	{
		int32 SizeOfElement = sizeof(T);
		return AddElement(SizeOfElement);
	}

	// Actual AddElement implementation
	int AddElement(int32 SizeOfElement);

	// Adds 1 to the Count
	void AddVertex();

	// Add the data to the vertex
	template <typename T>
	void AddData(const T& data, int32 elementID)
	{
		AddData((const void*)&data, elementID);
	}

	void AddData(const void* data, int32 elementID);
};