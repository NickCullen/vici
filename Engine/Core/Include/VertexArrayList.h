#pragma once

#include "CoreAPI.h"
#include "VTypes.h"
#include "Delegate.h"

typedef uint32 VAO_t;

// Delegate definitions
typedef VDelegate<void(*)(class VVertexArrayList*)> UpdateVertexListDelegate;

class CORE_API VVertexArrayList
{
	struct VAOInstance
	{
		VAO_t VAO;	// The GL reference to the vertex array
		uint32 Context;	// The ID of the context this VAO has been set for
	};

private:
	UpdateVertexListDelegate OnUpdateVertexListDelegate;	// Called when vertex list needs updating
public:
	
};