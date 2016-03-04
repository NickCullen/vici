#include "PrimitiveShapes.h"
#include "VertexBuffer.h"
#include "Mesh.h"
#include "VTypes.h"
#include "Shader.h"	// Need shader IN constants

VPrimitiveShapes::VPrimitiveShapes()
{

}

VPrimitiveShapes::~VPrimitiveShapes()
{

}

VMesh* VPrimitiveShapes::CreateFromData(void* data, int sizeOfData, int sizePerVertex)
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

VMesh* VPrimitiveShapes::CreateTriangle()
{
	// Pos3 / rgb / uv2 / normal3
	static float32 vertexData[] = {
		0.0f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f
	};

	VMesh* mesh = CreateFromData(vertexData, sizeof(vertexData), sizeof(float32) * 6);
	if (mesh)
	{
		VVertexBuffer* vb = mesh->VertexBuffer;

		// Set vertex element info so it knows how to send to the 
		// shader vertex array
		int32 posID = vb->AddElement(sizeof(float32) * 3, false);
		vb->SetElementInfo(posID, VElementInfo(SHADER_IN_POSITION_ID, 3));

		int32 colID = vb->AddElement(sizeof(float32) * 3, false);
		vb->SetElementInfo(colID, VElementInfo(SHADER_IN_COLOR_ID, 3));

		// Return the mesh
		return mesh;
	}
	else
		return nullptr;
}