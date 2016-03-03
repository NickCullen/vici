#pragma once

#include "CoreAPI.h"
#include "Singleton.h"
#include "VertexArrayList.h"

class CORE_API VEngine : public VSingleton<VEngine>, IVertexArrayHandler
{
private:

public:
	VEngine();
	~VEngine();

	bool Init(int argc, const char** argv);

	void Render();

	void BindArrays(const VVertexArrayList& list) override;

};