#include "PIL/Graphics/MeshData.h"
#include "PIL/Graphics/VertexBuffer.h"
#include "PIL/Graphics/IndexBuffer.h"
#include "PIL/Graphics/MeshRenderer.h"

VMeshData::VMeshData()
	:VertexBuffer(nullptr),
	IndexBuffer(nullptr)
{

}

VMeshData::~VMeshData()
{
	if (VertexBuffer)
		delete(VertexBuffer);
	if (IndexBuffer)
		delete(IndexBuffer);
}

void VMeshData::BindBuffers(VMeshRenderer* Renderer)
{
	VertexBuffer->Bind();
	VertexBuffer->SetElementsInShader(Renderer->GetShader());
	IndexBuffer->Bind();
}

void VMeshData::SetVertexBuffer(VVertexBuffer* vertexBuffer)
{
	VertexBuffer = vertexBuffer;
}
void VMeshData::SetIndexBuffer(VIndexBuffer* indexBuffer)
{
	IndexBuffer = indexBuffer;
}

void VMeshData::DrawElements()
{
	IndexBuffer->DrawElements();
}