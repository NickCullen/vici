#include "Engine.h"
#include "Renderer.h"
#include <stdio.h>

// Temp
#include "Shader.h"
#include "Glew.h"
#include "Mesh.h"
#include "PrimitiveShapes.h"
#include "Texture2D.h"

VShader* Shader;
VMesh* Mesh1;
VTexture2D* Texture;


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

//THIS IS ALL TEST CODE FOR NOW
bool VEngine::Init(int argc, const char** argv)
{
	if (!VRenderer::Init())
		return false;

	Mesh1 = VPrimitiveShapes::CreateQuad();

	const char* vPath = "C:\\Users\\Nick\\Desktop\\vici\\Resources\\Shaders\\test.vert";
	const char* fPath = "C:\\Users\\Nick\\Desktop\\vici\\Resources\\Shaders\\test.frag";
	Shader = new VShader();
	Shader->Load(vPath, fPath);
	Shader->BindFragDataLocation(SHADER_OUT_COLOR_ID, 0);

	// Set shader that will be used to render mesh
	Mesh1->SetShader(Shader);

	// checker board
	float pixels[] = {
		0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
	};

	Texture = new VTexture2D();
	if (Texture->Lock())
	{
		Texture->SetSize(2, 2);
		Texture->FromArray(pixels, sizeof(pixels));
		Texture->SetMinFilterMetho(FILTER_NEAREST);
		Texture->SetMagFilterMetho(FILTER_NEAREST);
		// Send to GPU
		Texture->Unlock();
	}

	return true;
}

//THIS IS ALL TEST CODE FOR NOW
void VEngine::Render()
{
	Texture->Bind();
	Mesh1->Render();

}