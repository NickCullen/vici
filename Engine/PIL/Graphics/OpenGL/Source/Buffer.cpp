#include "PIL/Graphics/Buffer.h"
#include "PIL/Graphics/OpenGL/Include/Glew.h"
#include <memory>

// OpenGL VBOHandle decleration
struct VBOHandle
{
	GLuint vbo;
};

VBuffer::VBuffer(EBufferType type, EBufferUse usage)
	:Data(nullptr),
	Count(0),
	Size(0),
	MaxSize(0),
	Type(type),
	Usage(usage)
{
	VBO = new VBOHandle();
	VBO->vbo = 0;
}

VBuffer::~VBuffer()
{
	Flush();
	delete(VBO);
}

uint32 VBuffer::BufferTypeToGL()
{
	switch (Type)
	{
	case ARRAY_BUFFER:		return GL_ARRAY_BUFFER;
	case ELEMENT_BUFFER:	return GL_ELEMENT_ARRAY_BUFFER;
	default:				return GL_ARRAY_BUFFER;		// Assume array buffer
	}
}


uint32 VBuffer::BufferUsageToGL()
{
	switch (Usage)
	{
	case STATIC_DRAW:		return GL_STATIC_DRAW;
	case DYNAMIC_DRAW:		return GL_DYNAMIC_DRAW;
	case STREAM_DRAW:		return GL_STREAM_DRAW;
	default:				return GL_STATIC_DRAW;	// Assume static
	}
}

void VBuffer::Resize(int32 NewSize)
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
	int32 ds = GetSingleItemDataSize();
	Count = ds != 0 ? Size / ds : 0;

}

void VBuffer::Bind()
{
	glBindBuffer(BufferTypeToGL(), VBO->vbo);
}

bool VBuffer::Lock()
{
	FlushGPUMemory();
	glGenBuffers(1, &VBO->vbo);

	if (VBO->vbo <= 0)
		return false;

	glBindBuffer(BufferTypeToGL(), VBO->vbo);

	return true;
}

void VBuffer::Unlock()
{
	glBufferData(BufferTypeToGL(), Size, Data, BufferUsageToGL());
}

void VBuffer::FlushClientMemory()
{
	if (Data != nullptr)
	{
		delete[] Data;
		Data = nullptr;
		Count = Size = MaxSize = 0;
	}
}

void VBuffer::FlushGPUMemory()
{
	if (VBO->vbo > 0)
	{
		glDeleteBuffers(1, &VBO->vbo);
		VBO->vbo = 0;
	}
}

void VBuffer::Flush()
{
	FlushGPUMemory();
	FlushClientMemory();
}

void VBuffer::FromArray(void* data, int32 sizeOfArray, int32 sizePerEntry)
{
	FlushClientMemory();	// Make sure we're cleaned out

	SetSingleItemDataSize(sizePerEntry);	// call child class set size fn
	Size = MaxSize = sizeOfArray;
	Count = Size / sizePerEntry;

	Data = (void*)new int8[Size];
	memcpy(Data, data, Size);
}
