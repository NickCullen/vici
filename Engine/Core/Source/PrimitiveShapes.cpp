#include "PrimitiveShapes.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Mesh.h"
#include "VTypes.h"
#include "Shader.h"	// Need shader IN constants

VPrimitiveShapes::VPrimitiveShapes()
{

}

VPrimitiveShapes::~VPrimitiveShapes()
{

}

VMesh* VPrimitiveShapes::CreateFromData(void* data, int sizeOfData, int sizePerVertex, uint32* indices, uint32 indexCount)
{
	VVertexBuffer* vb = new VVertexBuffer();
	if (vb->Lock())
	{
		// Update vertex data
		vb->FromArray(data, sizeOfData, sizePerVertex);
		vb->Unlock();

		// create index data
		VIndexBuffer* ib = new VIndexBuffer();
		if (ib->Lock())
		{
			ib->FromArray(indices, indexCount * sizeof(uint32), sizeof(uint32));
			ib->Unlock();

			VMesh* retMesh = new VMesh();
			retMesh->SetVertexBuffer(vb);
			retMesh->SetIndexBuffer(ib);
			return retMesh;
		}
		else
		{
			delete(vb);
			delete(ib);
			return nullptr;
		}
	}
	else
	{
		delete(vb);
		return nullptr;
	}
}

VMesh* VPrimitiveShapes::CreateTriangle()
{
	// Pos3
	static float32 vertexData[] = {
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f 
	};

	static uint32 indexData[] = {
		0, 1, 2
	};

	VMesh* mesh = CreateFromData(vertexData, sizeof(vertexData), sizeof(float32) * 3, indexData, 3);
	if (mesh)
	{
		VVertexBuffer* vb = mesh->VertexBuffer;

		// Set vertex element info so it knows how to send to the 
		// shader vertex array
		int32 posID = vb->AddElement(sizeof(float32) * 3, false);
		vb->SetElementInfo(posID, VElementInfo(SHADER_IN_POSITION_ID, 3));

		// Return the mesh
		return mesh;
	}
	else
		return nullptr;
}

VMesh* VPrimitiveShapes::CreateQuad()
{
	// Pos3 
	static float32 vertexData[] = {
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f
	};

	static uint32 indexData[] = {
		0, 1, 2,
		3, 0, 2
	};

	VMesh* mesh = CreateFromData(vertexData, sizeof(vertexData), sizeof(float32) * 3, indexData, 6);
	if (mesh)
	{
		VVertexBuffer* vb = mesh->VertexBuffer;

		// Set vertex element info so it knows how to send to the 
		// shader vertex array
		int32 posID = vb->AddElement(sizeof(float32) * 3, false);
		vb->SetElementInfo(posID, VElementInfo(SHADER_IN_POSITION_ID, 3));

		// Return the mesh
		return mesh;
	}
	else
		return nullptr;
}