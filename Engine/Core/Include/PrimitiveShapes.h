#pragma once

class VMesh;
class VVertexBuffer;

#include "CoreAPI.h"

class CORE_API VPrimitiveShapes
{
private:

	static VMesh* CreateFromData(void* data, int sizeOfData, int sizePerVertex);

public:
	VPrimitiveShapes();

	~VPrimitiveShapes();

	static VMesh* CreateTriangle();
};