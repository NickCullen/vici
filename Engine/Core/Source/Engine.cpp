#include "Engine.h"
#include "Renderer.h"
#include <stdio.h>

// Temp
#include "Shader.h"
#include "Glew.h"
#include "Mesh.h"
#include "PrimitiveShapes.h"

VShader* Shader;
VMesh* Mesh;

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

	Mesh = VPrimitiveShapes::CreateQuad();

	const char* vPath = "C:\\Users\\Nick\\Desktop\\vici\\Resources\\Shaders\\test.vert";
	const char* fPath = "C:\\Users\\Nick\\Desktop\\vici\\Resources\\Shaders\\test.frag";
	Shader = new VShader();
	Shader->Load(vPath, fPath);
	Shader->BindFragDataLocation(SHADER_OUT_COLOR_ID, 0);

	// Set shader that will be used to render mesh
	Mesh->SetShader(Shader);

	return true;
}

//THIS IS ALL TEST CODE FOR NOW
void VEngine::Render()
{
	Mesh->Render();
}