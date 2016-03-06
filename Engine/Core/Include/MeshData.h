#pragma once

#include "CoreAPI.h"

class VVertexBuffer;
class VIndexBuffer;

class CORE_API VMeshData
{
	friend class VPrimitiveShapes;
private:
	VVertexBuffer* VertexBuffer;	// Vertex data for this mesh

	VIndexBuffer* IndexBuffer;		// Indices into the vertex buffer

public:
	VMeshData();

	~VMeshData();

	// Uses the mesh datas indices to render this mesh
	void DrawElements();

	// Binds The buffers for this mesh data
	void BindBuffers(class VMeshRenderer* Renderer);

	// Setters
	void VMeshData::SetVertexBuffer(VVertexBuffer* vertexBuffer);
	void VMeshData::SetIndexBuffer(VIndexBuffer* indexBuffer);
};