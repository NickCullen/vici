#include "MeshRenderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Glew.h"
#include "MeshData.h"

VMeshRenderer::VMeshRenderer()
	:MeshData(nullptr),
	Shader(nullptr)
{
	// Let the array list know that this mesh is in charge of it
	VertexArrayList.SetHandler(this);	
}

VMeshRenderer::~VMeshRenderer()
{
}

bool VMeshRenderer::BindArrays(const VVertexArrayList& list)
{
	// Only bother binding if something is going to actually render this mesh
	if (Shader)
	{
		MeshData->BindBuffers(this);
		return true;
	}
	return false;
}

void VMeshRenderer::Render()
{
	if (Shader)
	{
		Shader->Use();	// User shader

		VertexArrayList.Bind();	// Bind the vertex arrays

		MeshData->DrawElements();	// Draw 
	}
}

void VMeshRenderer::SetShader(VShader* shader)
{
	Shader = shader;
	if (Shader)
	{
		// force binding of array
		VertexArrayList.BindForceNotify();
	}
}

void VMeshRenderer::SetMeshData(VMeshData* data)
{
	MeshData = data;
	if (MeshData)
	{
		VertexArrayList.BindForceNotify();
	}
}