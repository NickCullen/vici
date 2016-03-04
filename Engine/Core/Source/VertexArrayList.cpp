#include "VertexArrayList.h"
#include "Glew.h"
#include "Renderer.h"

VVertexArrayList::VVertexArrayList()
	:Handler(nullptr)
{
}

VVertexArrayList::VVertexArrayList(IVertexArrayHandler* handler)
	:Handler(handler)
{
}

VVertexArrayList::~VVertexArrayList()
{

}

bool VVertexArrayList::DoesVAOExist()
{
	// if not equal to -1 then this VAO has been allocated for this context
	return VAO[VRenderer::GetInstance()->GetContextID()] != 0 ? true : false;
}

void VVertexArrayList::AllocVAOAndNotify()
{
	int32 currentContextID = VRenderer::GetInstance()->GetContextID();

	glGenVertexArrays(1, &VAO[currentContextID]);
	glBindVertexArray(VAO[currentContextID]);
	
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
		glBindVertexArray(VAO[currentContextID]);
	}

}

void VVertexArrayList::BindNoNotify()
{
	int32 currentContextID = VRenderer::GetInstance()->GetContextID();
	if (!DoesVAOExist())
		glGenVertexArrays(1, &VAO[currentContextID]);

	glBindVertexArray(VAO[currentContextID]);
}

void VVertexArrayList::BindForceNotify()
{
	// We got to make sure the VAO exists at least
	if (!DoesVAOExist())
		AllocVAOAndNotify();
	else
	{
		int32 currentContextID = VRenderer::GetInstance()->GetContextID();
		glBindVertexArray(VAO[currentContextID]);

		// Notify handler to bind arrays
		Handler->BindArrays(*this);
	}
}