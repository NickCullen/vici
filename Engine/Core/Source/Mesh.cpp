#include "Mesh.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Glew.h"

VMesh::VMesh()
	:VertexBuffer(nullptr),
	Shader(nullptr)
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

	int32 posAttrib = Shader->GetPositionLocation();

	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void VMesh::SetVertexBuffer(VVertexBuffer* vertexBuffer)
{
	VertexBuffer = vertexBuffer;
}

void VMesh::Render()
{
	if (Shader)
	{
		Shader->Use();

		VertexArrayList.Bind();
	}
}

void VMesh::SetShader(VShader* shader)
{
	Shader = shader;
}