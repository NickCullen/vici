#pragma once

class VVertexBuffer;
class VIndexBuffer;
class VShader;	

#include "CoreAPI.h"
#include "VertexArrayList.h"

class CORE_API VMesh : public IVertexArrayHandler
{
	friend class VPrimitiveShapes;

private:
	VVertexArrayList VertexArrayList;	// The list of vertex arrays for this mesh

	VVertexBuffer* VertexBuffer;	// Vertex data for this mesh

	VIndexBuffer* IndexBuffer;		// Indices into the vertex buffer

	VShader* Shader;				// Shader used to render this mesh (should be material - placeholder)
public:
	VMesh();

	~VMesh();

	void BindArrays(const VVertexArrayList& list) override;

	void Render();

	void SetVertexBuffer(VVertexBuffer* vertexBuffer);
	void SetIndexBuffer(VIndexBuffer* indexBuffer);
	void SetShader(VShader* shader);
};