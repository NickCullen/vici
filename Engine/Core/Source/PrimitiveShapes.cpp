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
	// Pos 2
	static float32 vertexData[] = {
		0.0f, 0.5f,
		-0.5f, -0.5f,
		0.5f, -0.5f 
	};

	static uint32 indexData[] = {
		0, 1, 2
	};

	static const int8 NUM_COMPONENTS = 2;

	VMesh* mesh = CreateFromData(vertexData, sizeof(vertexData), sizeof(float32) * NUM_COMPONENTS, indexData, 3);
	if (mesh)
	{
		VVertexBuffer* vb = mesh->VertexBuffer;

		// Set vertex element info so it knows how to send to the 
		// shader vertex array
		int32 posID = vb->AddElement(sizeof(float32) * NUM_COMPONENTS, false);
		vb->SetElementInfo(posID, VElementInfo(SHADER_IN_POSITION_ID, NUM_COMPONENTS));

		// Return the mesh
		return mesh;
	}
	else
		return nullptr;
}

VMesh* VPrimitiveShapes::CreateSquare()
{
	// Pos2 
	static float32 vertexData[] = {
		-0.5f, 0.5f,
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f
	};

	static uint32 indexData[] = {
		0, 1, 2,
		3, 0, 2
	};

	static const int8 NUM_COMPONENTS = 2;

	VMesh* mesh = CreateFromData(vertexData, sizeof(vertexData), sizeof(float32) * NUM_COMPONENTS, indexData, 6);
	if (mesh)
	{
		VVertexBuffer* vb = mesh->VertexBuffer;

		// Set vertex element info so it knows how to send to the 
		// shader vertex array
		int32 posID = vb->AddElement(sizeof(float32) * NUM_COMPONENTS, false);
		vb->SetElementInfo(posID, VElementInfo(SHADER_IN_POSITION_ID, NUM_COMPONENTS));

		// Return the mesh
		return mesh;
	}
	else
		return nullptr;
}

VMesh* VPrimitiveShapes::CreateQuad()
{
	// Pos2 / uv2
	static float32 vertexData[] = {
		-0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 1.0f, 1.0f,
	};

	static uint32 indexData[] = {
		0, 1, 2,
		3, 0, 2
	};

	VMesh* mesh = CreateFromData(vertexData, sizeof(vertexData), sizeof(float32) * 4, indexData, 6);
	if (mesh)
	{
		VVertexBuffer* vb = mesh->VertexBuffer;

		// Set vertex element info so it knows how to send to the 
		// shader vertex array
		int32 posID = vb->AddElement(sizeof(float32) * 2, false);
		vb->SetElementInfo(posID, VElementInfo(SHADER_IN_POSITION_ID, 2));

		int32 uvID = vb->AddElement(sizeof(float32) * 2, false);
		vb->SetElementInfo(uvID, VElementInfo(SHADER_IN_UV1_ID, 2));
		// Return the mesh
		return mesh;
	}
	else
		return nullptr;
}