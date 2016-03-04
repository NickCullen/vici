#pragma once

class VVertexBuffer;
class VShader;	

#include "CoreAPI.h"
#include "VertexArrayList.h"

class CORE_API VMesh : public IVertexArrayHandler
{
private:
	VVertexArrayList VertexArrayList;	// The list of vertex arrays for this mesh

	VVertexBuffer* VertexBuffer;	// Vertex data for this mesh

	VShader* Shader;				// Shader used to render this mesh (should be material - placeholder)
public:
	VMesh();

	~VMesh();

	void BindArrays(const VVertexArrayList& list) override;

	void Render();

	void SetVertexBuffer(VVertexBuffer* vertexBuffer);
	void SetShader(VShader* shader);
};