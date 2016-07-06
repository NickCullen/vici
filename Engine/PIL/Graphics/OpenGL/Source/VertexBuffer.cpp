#include "PIL/Graphics/VertexBuffer.h"
#include "PIL/Graphics/OpenGL/Include/Glew.h"
#include <memory>
#include "PIL/Graphics/Shader.h"
#include "PIL/Graphics/Renderer.h"

VVertexBuffer::VVertexBuffer(EBufferUse usage)
	:VBuffer(ARRAY_BUFFER, usage),
	NumOfElements(0),
	VertexSize(0)
{

}

VVertexBuffer::~VVertexBuffer()
{

}

int32 VVertexBuffer::GetSingleItemDataSize()
{
	return VertexSize;
}

void VVertexBuffer::SetSingleItemDataSize(int32 size)
{
	VertexSize = size;
}

void VVertexBuffer::AllocateVertices(int32 Count)
{
	Resize(Count * VertexSize);
}

int32 VVertexBuffer::AddElement(int32 SizeOfElement, bool EffectVertexSize)
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
	if(EffectVertexSize) VertexSize += newElement->Size;

	// Increment
	NumOfElements++;
	
	// Return id
	return id;
}

void VVertexBuffer::SetElementInfo(int32 id, const VElementInfo& info)
{
	Elements[id].Info = info;
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

void VVertexBuffer::SetElementsInShader(VShader* shader)
{
	for (int i = 0; i < NumOfElements; i++)
	{
		VVertexElement* e = &Elements[i];

		VShaderInputHandle* attribID = shader->AttributeLocation(e->Info.ShaderID);
		if (attribID != nullptr)
		{
			shader->EnableVertexArray(attribID);
			shader->VertexAttribPointer(attribID, e, VertexSize);
		}
	}
}