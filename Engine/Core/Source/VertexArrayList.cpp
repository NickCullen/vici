#include "VertexArrayList.h"
#include "Glew.h"
#include "Renderer.h"

VVertexArrayList::VVertexArrayList()
	:OnUpdateVertexListDelegate(nullptr)
{
	for (int i = 0; i < MAX_RENDER_CONTEXTS; i++)
		VAO[i].Context = -1;
}

VVertexArrayList::~VVertexArrayList()
{

}

bool VVertexArrayList::DoesVAOExist()
{
	int32 currentContextID = VRenderer::GetInstance()->GetContextID();
	for (int i = 0; i < MAX_RENDER_CONTEXTS && VAO[i].Context != -1; i++)
	{
		if (VAO[i].Context == currentContextID)
			return true;
	}

	return false;
}

void VVertexArrayList::AllocVAOAndNotify()
{
	int32 currentContextID = VRenderer::GetInstance()->GetContextID();
	for (int i = 0; i < MAX_RENDER_CONTEXTS; i++)
	{
		if (VAO[i].Context == -1)
		{
			VAO[i].Context = currentContextID;
			glGenVertexArrays(1, &VAO[i].VAO);

			//Notify
			OnUpdateVertexListDelegate(this);

			break;
		}
	}
}

void VVertexArrayList::Bind()
{
	if (!DoesVAOExist())
		AllocVAOAndNotify();
}