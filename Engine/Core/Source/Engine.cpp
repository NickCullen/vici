#include "Engine.h"
#include "Renderer.h"
#include <stdio.h>

// Temp
#include "Shader.h"
#include "Glew.h"
#include "Mesh.h"
#include "PrimitiveShapes.h"
#include "Texture2D.h"
#include "Vector4.h"
#include "FilePath.h"

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

	VFilePath vPath("Shaders\\test.vert", FILE_EDITOR_RESOURCE_DIRECTORY);
	VFilePath fPath("Shaders\\test.frag", FILE_EDITOR_RESOURCE_DIRECTORY);

	Shader = new VShader();
	Shader->Load(vPath, fPath);
	Shader->BindFragDataLocation(SHADER_OUT_COLOR_ID, 0);

	// Set shader that will be used to render mesh
	Mesh1->SetShader(Shader);

	VFilePath fp("Textures/test.png", FILE_EDITOR_RESOURCE_DIRECTORY);

	Texture = VTexture2D::FromFile(fp);


	return true;
}

//THIS IS ALL TEST CODE FOR NOW
void VEngine::Render()
{
	Texture->Bind();
	Mesh1->Render();

}