#pragma once

class VMeshData;
class VVertexBuffer;

#include "CoreAPI.h"
#include "VTypes.h"

class CORE_API VPrimitiveShapes
{
private:

	static VMeshData* CreateFromData(void* data, int sizeOfData, int sizePerVertex, uint32* indices, uint32 indexCount);

public:
	VPrimitiveShapes();

	~VPrimitiveShapes();

	
	static VMeshData* CreateTriangle();
	static VMeshData* CreateSquare();
	static VMeshData* CreateQuad();		// Quad differs from square such that it contains UV info
};