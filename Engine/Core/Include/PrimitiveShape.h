#pragma once

class VMesh;
class VVertexBuffer;

#include "CoreAPI.h"

class CORE_API VPrimitiveShape
{
private:

	static VMesh* CreateFromData(void* data, int sizeOfData, int sizePerVertex);

public:
	VPrimitiveShape();

	~VPrimitiveShape();

	static VMesh* CreateTriangle();
};