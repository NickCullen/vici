#include "PrimitiveShape.h"
#include "VertexBuffer.h"
#include "Mesh.h"
#include "VTypes.h"

VPrimitiveShape::VPrimitiveShape()
{

}

VPrimitiveShape::~VPrimitiveShape()
{

}

VMesh* VPrimitiveShape::CreateFromData(void* data, int sizeOfData, int sizePerVertex)
{
	VVertexBuffer* vb = new VVertexBuffer();
	if (vb->Lock())
	{
		vb->FromArray(data, sizeOfData, sizePerVertex);

		vb->Unlock();

		VMesh* retMesh = new VMesh();
		retMesh->SetVertexBuffer(vb);
		return retMesh;
	}
	else
	{
		delete(vb);
		return nullptr;
	}
}

VMesh* VPrimitiveShape::CreateTriangle()
{
	// Pos3 / uv2 / normal3
	static float32 vertexData[] = {
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};

	return CreateFromData(vertexData, sizeof(vertexData), sizeof(float32) * 3);
}