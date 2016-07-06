#include "PIL/Graphics/IndexBuffer.h"
#include "PIL/Graphics/OpenGL/Include/Glew.h"

VIndexBuffer::VIndexBuffer(EIndexType indexType, EBufferUse usage)
	:VBuffer(ELEMENT_BUFFER, usage),
	IndexType(indexType)
{
}

VIndexBuffer::~VIndexBuffer()
{

}

uint32 VIndexBuffer::IndexTypeToGL()
{
	switch (IndexType)
	{
		case INDEX_TYPE_POINTS:				return GL_POINTS;
		case INDEX_TYPE_LINES: 				return GL_LINES;
		case INDEX_TYPE_LINE_LOOP:			return GL_LINE_LOOP;
		case INDEX_TYPE_LINE_STRIP:			return GL_LINE_STRIP;
		case INDEX_TYPE_TRIANGLES:			return GL_TRIANGLES;
		case INDEX_TYPE_TRIANGLE_STRIP:		return GL_TRIANGLE_STRIP;
		case INDEX_TYPE_TRIANGLE_FAN:		return GL_TRIANGLE_FAN;
		case INDEX_TYPE_QUADS:				return GL_QUADS;
		case INDEX_TYPE_QUAD_STRIP:			return GL_QUAD_STRIP;
		case INDEX_TYPE_POLYGON:			return GL_POLYGON;
		default:							return GL_TRIANGLES;	// Assume triangles
	}
}

int32 VIndexBuffer::GetSingleItemDataSize()
{
	return sizeof(uint32);	// Always unsigned int
}

void VIndexBuffer::SetSingleItemDataSize(int32 size)
{
	//Ignored
}

void VIndexBuffer::DrawElements()
{
	glDrawElements(IndexTypeToGL(), Count, GL_UNSIGNED_INT, 0);
}