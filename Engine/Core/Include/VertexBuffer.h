#pragma once

#include "CoreAPI.h"
#include "VTypes.h"

// max number of elements per vertex - 24 is way more than enough
static const int MAX_BUFFER_ELEMENTS = 24;

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

	// Adds an element and returns the id of it
	template<typename T>
	int AddElement()
	{
		int32 SizeOfElement = sizeof(T);
		return AddElement(SizeOfElement);
	}

	// Actual AddElement implementation
	int AddElement(int32 SizeOfElement);

	//Add Data

};