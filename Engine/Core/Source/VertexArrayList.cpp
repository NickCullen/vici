#include "VertexArrayList.h"
#include "Glew.h"
#include "Renderer.h"

VVertexArrayList::VVertexArrayList()
	:Handler(nullptr)
{
	for (int i = 0; i < MAX_RENDER_CONTEXTS; i++)
		VAO[i].Context = -1;
}

VVertexArrayList::VVertexArrayList(IVertexArrayHandler* handler)
	:Handler(handler)
{
	for (int i = 0; i < MAX_RENDER_CONTEXTS; i++)
		VAO[i].Context = -1;
}

VVertexArrayList::~VVertexArrayList()
{

}

bool VVertexArrayList::DoesVAOExist()
{
	// if not equal to -1 then this VAO has been allocated for this context
	return VAO[VRenderer::GetInstance()->GetContextID()].Context != -1 ? true : false;
}

void VVertexArrayList::AllocVAOAndNotify()
{
	int32 currentContextID = VRenderer::GetInstance()->GetContextID();
	VAO[currentContextID].Context = currentContextID;

	glGenVertexArrays(1, &VAO[currentContextID].VAO);
	glBindVertexArray(VAO[currentContextID].VAO);

	// Notify handler to bind arrays
	Handler->BindArrays(*this);
}

void VVertexArrayList::Bind()
{
	if (!DoesVAOExist())
		AllocVAOAndNotify();
	else
	{
		int32 currentContextID = VRenderer::GetInstance()->GetContextID();
		glBindVertexArray(VAO[currentContextID].VAO);
	}

}