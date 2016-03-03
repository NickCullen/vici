#include "Engine.h"
#include "Renderer.h"
#include <stdio.h>

// Temp
#include "Shader.h"
#include "VertexBuffer.h"
#include "Glew.h"
#include "Vector3.h"
#include "VertexArrayList.h"

VShader* Shader;
VVertexBuffer* VertexBuffer;
VVertexArrayList* VertexArrayList;

GLuint vao[3];

VEngine::VEngine()
	:VSingleton(this)
{
	
}

VEngine::~VEngine()
{

}

void Callback(VVertexArrayList* list)
{

}

void VEngine::BindArrays(const VVertexArrayList& list)
{
	VertexBuffer->Bind();

	int32 posAttrib = Shader->GetPositionLocation();

	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

}

bool VEngine::Init(int argc, const char** argv)
{
	if (!VRenderer::Init())
		return false;


	float positions[] = { 0.0f, 0.5f,
						  0.5f, -0.5f,
						 -0.5f, -0.5f };


	VertexArrayList = new VVertexArrayList(this);

	const char* vPath = "C:\\Users\\Nick\\Desktop\\vici\\Resources\\Shaders\\test.vert";
	const char* fPath = "C:\\Users\\Nick\\Desktop\\vici\\Resources\\Shaders\\test.frag";
	Shader = new VShader();
	Shader->Load(vPath, fPath);
	Shader->BindFragDataLocation("outColor", 0);

	VertexBuffer = new VVertexBuffer();
	if (VertexBuffer->Lock())
	{
		VertexBuffer->FromArray(positions, sizeof(positions), sizeof(float) * 2);

		VertexBuffer->Unlock();
	}

	VertexArrayList->Bind();

	return true;
}

void VEngine::Render()
{
	Shader->Use();
	VertexArrayList->Bind();

	glDrawArrays(GL_TRIANGLES, 0, 3);

}