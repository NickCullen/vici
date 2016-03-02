#include "Engine.h"
#include "Renderer.h"

// Temp
#include "Shader.h"
#include "VertexBuffer.h"
#include "GL/glew.h"

VShader* Shader;
VVertexBuffer* VertexBuffer;
GLuint vao;

struct VEC2
{
	float x;
	float y;

	VEC2(float _x, float _y)
	{
		x = _x; y = _y;
	}
};

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

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

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

	int32 posAttrib = Shader->PositionLocation();
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);

	return true;
}

void VEngine::Render()
{
	Shader->Use();

	
	glBindVertexArray(vao);


	glDrawArrays(GL_TRIANGLES, 0, 3);
}