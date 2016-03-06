#pragma once

#include "CoreAPI.h"
#include "VertexArrayList.h"

class VShader;	
class VMeshData;
class VMaterial;

class CORE_API VMeshRenderer : public IVertexArrayHandler
{
private:
	VVertexArrayList VertexArrayList;	// The list of vertex arrays for this mesh

	VMeshData* MeshData;			// The mesh that this renderer will draw

	VMaterial* Material;			// material for this mesh

public:
	VMeshRenderer();

	~VMeshRenderer();

	bool BindArrays(const VVertexArrayList& list) override;

	void Render();

	// Setters
	void SetMaterial(VMaterial* material);
	void SetMeshData(VMeshData* data);

	// Getters
	inline VShader* GetShader();
};