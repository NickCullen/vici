#include "PIL/Graphics/VertexArrayList.h"
#include "PIL/Graphics/OpenGL/Include/Glew.h"
#include "PIL/Graphics/Renderer.h"

// VAO Decleration
struct VAOHandle
{
	GLuint vao;
};

VVertexArrayList::VVertexArrayList()
	:Handler(nullptr)
{
#if VICI_EDITOR
	memset(VAO, NULL, sizeof(VAO));
#else
	VAO[0] = NULL;
#endif
}

VVertexArrayList::VVertexArrayList(IVertexArrayHandler* handler)
	:Handler(handler)
{
#if VICI_EDITOR
	memset(VAO, NULL, sizeof(VAO));
#else
	VAO[0] = NULL;
#endif
}

VVertexArrayList::~VVertexArrayList()
{
	for (int i = 0; i < MAX_RENDER_CONTEXTS; i++)
	{
		if (VAO[i] != nullptr)
			glDeleteVertexArrays(1, &VAO[i]->vao);
	}
}

bool VVertexArrayList::DoesVAOExist()
{
	// if not equal to -1 then this VAO has been allocated for this context
	return VAO[VRenderer::GetInstance()->GetContextID()] != NULL;
}

void VVertexArrayList::AllocVAOAndNotify()
{
	int32 currentContextID = VRenderer::GetInstance()->GetContextID();

	VAO[currentContextID] = new VAOHandle();

	glGenVertexArrays(1, &VAO[currentContextID]->vao);
	glBindVertexArray(VAO[currentContextID]->vao);
	
	// Notify handler to bind arrays
	// If it returns false (failed to bind arrays) then destroy this vertex buffer
	if (!Handler->BindArrays(*this))
	{
		glDeleteVertexArrays(1, &VAO[currentContextID]->vao);
		VAO[currentContextID] = 0;
	}
}

void VVertexArrayList::Bind()
{
	if (!DoesVAOExist())
		AllocVAOAndNotify();
	else
	{
		int32 currentContextID = VRenderer::GetInstance()->GetContextID();
		glBindVertexArray(VAO[currentContextID]->vao);
	}

}

void VVertexArrayList::BindNoNotify()
{
	int32 currentContextID = VRenderer::GetInstance()->GetContextID();
	if (!DoesVAOExist())
		glGenVertexArrays(1, &VAO[currentContextID]->vao);

	glBindVertexArray(VAO[currentContextID]->vao);
}

void VVertexArrayList::BindForceNotify()
{
	// We got to make sure the VAO exists at least
	if (!DoesVAOExist())
		AllocVAOAndNotify();
	else
	{
		int32 currentContextID = VRenderer::GetInstance()->GetContextID();
		glBindVertexArray(VAO[currentContextID]->vao);

		// Notify handler to bind arrays
		Handler->BindArrays(*this);
	}
}