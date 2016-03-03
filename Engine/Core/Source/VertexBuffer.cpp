#include "VertexBuffer.h"
#include "Glew.h"
#include <memory>

VVertexBuffer::VVertexBuffer(EBufferType type, EBufferUse usage)
	:Data(nullptr),
	NumOfElements(0),
	VertexSize(0),
	VBO(0),
	Type(type),
	Usage(usage),
	Size(0),
	MaxSize(0),
	Count(0)
{

}

VVertexBuffer::~VVertexBuffer()
{
	// Make sure we clean up after ourselves
	Flush();
}

uint32 VVertexBuffer::BufferTypeToGL()
{
	switch (Type)
	{
		case ARRAY_BUFFER:		return GL_ARRAY_BUFFER;
		case ELEMENT_BUFFER:	return GL_ELEMENT_ARRAY_BUFFER;
		default:				return GL_ARRAY_BUFFER;		// Assume array buffer
	}
}

uint32 VVertexBuffer::BufferUsageToGL()
{
	switch (Usage)
	{
		case STATIC_DRAW:		return GL_STATIC_DRAW;
		case DYNAMIC_DRAW:	return GL_DYNAMIC_DRAW;
		case STREAM_DRAW:		return GL_STREAM_DRAW;
		default:				return GL_STATIC_DRAW;	// Assume static
	}
}

void VVertexBuffer::Resize(int32 NewSize)
{
	// Make sure Size doesnt exceed NewSize for when we copy data over
	if (NewSize < Size) Size = NewSize;

	void* NewData = (void*)new int8[NewSize];	// Allocate

	if (Size > 0)
	{
		memcpy(NewData, Data, Size);	// Copy over data
		delete[] Data;
	}
	
	Data = NewData;
	MaxSize = NewSize;
	Count = VertexSize != 0 ? Size / VertexSize : 0;

}

void VVertexBuffer::Bind()
{
	glBindBuffer(BufferTypeToGL(), VBO);
}

bool VVertexBuffer::Lock()
{
	FlushGPUMemory();
	glGenBuffers(1, &VBO);

	if (VBO <= 0)
		return false;

	glBindBuffer(BufferTypeToGL(), VBO);

	return true;
}

void VVertexBuffer::Unlock()
{
	glBufferData(BufferTypeToGL(), Size, Data, BufferUsageToGL());
}

void VVertexBuffer::FlushClientMemory()
{
	if (Data != nullptr)
	{
		delete[] Data;
		Data = nullptr;
		Count = Size = MaxSize = 0;
	}
}

void VVertexBuffer::FlushGPUMemory()
{
	if (VBO > 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}
}

void VVertexBuffer::Flush()
{
	FlushGPUMemory();
	FlushClientMemory();
}

void VVertexBuffer::AllocateVertices(int32 Count)
{
	Resize(Count * VertexSize);
}

int VVertexBuffer::AddElement(int32 SizeOfElement)
{
	// Cannot create more than MAX_BUFFER_ELEMENTS
	if (NumOfElements + 1 > MAX_ELEMENTS_PER_VERTEX)
		return -1;

	int32 id = NumOfElements;	// ID Is equal to number of elements

	VVertexElement* newElement = &Elements[id];	// The new element

	int32 offset = 0;

	//Work out its offset
	for (int i = 0; i < NumOfElements; i++)
		offset += Elements[i].Size;


	newElement->Size = SizeOfElement;
	newElement->Offset = offset;

	// Add this to the size per vertex
	VertexSize += newElement->Size;

	// Increment
	NumOfElements++;

	// Return id
	return id;
}

void VVertexBuffer::AddVertex()
{
	int32 newCount = Count + 1;
	if (newCount * VertexSize > MaxSize)
		Resize((newCount * VertexSize) + ((newCount * VertexSize) >> 1));

	Count = newCount;
	Size = Count * VertexSize;
}

void VVertexBuffer::AddData(const void* data, int32 elementID)
{
	int32 vertexIndex = VertexSize * (Count - 1);
	VVertexElement* ve = &Elements[elementID];

	memcpy((int8*)Data + vertexIndex + ve->Offset, data, ve->Size);
}

void VVertexBuffer::FromArray(void* data, int32 size, int32 sizePerVertex)
{
	FlushClientMemory();	// Make sure we're cleaned out

	VertexSize = sizePerVertex;
	Size = MaxSize = size;
	Count = size / sizePerVertex;

	Data = (void*)new int8[Size];
	memcpy(Data, data, Size);
}