#include "PIL/Graphics/IndexBuffer.h"
#include "PIL/Graphics/OpenGL/Include/Glew.h"
#include "PIL/Graphics/OpenGL/Include/GLTypeConverters.h"

VIndexBuffer::VIndexBuffer(EIndexType indexType, EBufferUse usage)
	:VBuffer(ELEMENT_BUFFER, usage),
	IndexType(indexType)
{
}

VIndexBuffer::~VIndexBuffer()
{

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
	glDrawElements(GLTypeConverter::IndexTypeToGL(IndexType), Count, GL_UNSIGNED_INT, 0);
}