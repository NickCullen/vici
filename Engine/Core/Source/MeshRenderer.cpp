#include "MeshRenderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Glew.h"
#include "MeshData.h"
#include "Material.h"


VMeshRenderer::VMeshRenderer()
	:MeshData(nullptr),
	Material(nullptr)
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
	if (Material)
	{
		MeshData->BindBuffers(this);
		return true;
	}
	return false;
}

void VMeshRenderer::Render()
{
	if (Material)
	{
		Material->PrepareForRender();	// Uses shader and sets up its parameters

		VertexArrayList.Bind();			// Bind the vertex arrays

		MeshData->DrawElements();		// Draw 

		Material->CleanupAfterRender();	// Cleanup
	}
}

void VMeshRenderer::SetMaterial(VMaterial* material)
{
	Material = material;
	if (Material)
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

VShader* VMeshRenderer::GetShader()
{
	return Material ? Material->GetShader() : nullptr;
}