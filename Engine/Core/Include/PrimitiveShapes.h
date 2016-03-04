#pragma once

class VMesh;
class VVertexBuffer;

#include "CoreAPI.h"
#include "VTypes.h"

class CORE_API VPrimitiveShapes
{
private:

	static VMesh* CreateFromData(void* data, int sizeOfData, int sizePerVertex, uint32* indices, uint32 indexCount);

public:
	VPrimitiveShapes();

	~VPrimitiveShapes();

	static VMesh* CreateTriangle();
	static VMesh* CreateQuad();
};