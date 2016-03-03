#include "Engine.h"
#include "Renderer.h"

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

bool VEngine::Init(int argc, const char** argv)
{
	if (!VRenderer::Init())
		return false;

	float positions[] = { 0.0f, 0.5f,
						  0.5f, -0.5f,
						 -0.5f, -0.5f };

	
	VertexArrayList = new VVertexArrayList();

	VertexArrayList->Bind();

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

	

	return true;
}

int count = 0;
int max = 3;

void VEngine::Render()
{
	
	if(vao[count] == 0)
		glGenVertexArrays(1, &vao[count]);
	glBindVertexArray(vao[count]);
	VertexBuffer->Bind();

	int32 posAttrib = Shader->GetPositionLocation();
	
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	

	Shader->Use();


	glDrawArrays(GL_TRIANGLES, 0, 3);

	//glDeleteVertexArrays(1, &vao[count]);

	count++;
	if (count >= max)
		count = 0;

}