#pragma once

#include "CoreAPI.h"
#include "VertexArrayList.h"

class VShader;	
class VMeshData;

class CORE_API VMeshRenderer : public IVertexArrayHandler
{
private:
	VVertexArrayList VertexArrayList;	// The list of vertex arrays for this mesh

	VMeshData* MeshData;			// The mesh that this renderer will draw

	VShader* Shader;				// Shader used to render this mesh (should be material - placeholder)
public:
	VMeshRenderer();

	~VMeshRenderer();

	bool BindArrays(const VVertexArrayList& list) override;

	void Render();

	// Setters
	void SetShader(VShader* shader);
	void SetMeshData(VMeshData* data);

	// Getters
	inline VShader* GetShader() { return Shader; }
};