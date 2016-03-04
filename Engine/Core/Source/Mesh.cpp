#include "Mesh.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Glew.h"

VMesh::VMesh()
	:VertexBuffer(nullptr),
	Shader(nullptr),
	IndexBuffer(nullptr)
{
	// Let the array list know that this mesh is in charge of it
	VertexArrayList.SetHandler(this);	
}

VMesh::~VMesh()
{
	if(VertexBuffer) delete(VertexBuffer);
}

void VMesh::BindArrays(const VVertexArrayList& list)
{
	VertexBuffer->Bind();
	VertexBuffer->SetElementsInShader(Shader);
	IndexBuffer->Bind();
}

void VMesh::SetVertexBuffer(VVertexBuffer* vertexBuffer)
{
	VertexBuffer = vertexBuffer;
}

void VMesh::SetIndexBuffer(VIndexBuffer* indexBuffer)
{
	IndexBuffer = indexBuffer;
}
void VMesh::Render()
{
	if (Shader)
	{
		Shader->Use();	// User shader

		VertexArrayList.Bind();	// Bind the vertex arrays

		IndexBuffer->DrawElements();	// Draw 
	}
}

void VMesh::SetShader(VShader* shader)
{
	Shader = shader;
	if (Shader)
	{
		// force binding of array
		VertexArrayList.BindForceNotify();
	}
}