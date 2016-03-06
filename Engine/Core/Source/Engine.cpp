#include "Engine.h"
#include "Renderer.h"
#include <stdio.h>

// Temp
#include "Shader.h"
#include "Glew.h"
#include "MeshRenderer.h"
#include "PrimitiveShapes.h"
#include "Texture2D.h"
#include "Vector4.h"
#include "FilePath.h"
#include "Renderer.h"
#include "Material.h"

VShader* Shader;
VMeshRenderer* MeshRenderer;
VTexture2D* Texture;
VTexture2D* Texture2;


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

	MeshRenderer = new VMeshRenderer();
	MeshRenderer->SetMeshData(VPrimitiveShapes::CreateQuad());

	VFilePath vPath("Shaders\\test.vert", FILE_EDITOR_RESOURCE_DIRECTORY);
	VFilePath fPath("Shaders\\test.frag", FILE_EDITOR_RESOURCE_DIRECTORY);

	Shader = new VShader();
	Shader->Load(vPath, fPath);
	Shader->BindFragDataLocation(SHADER_OUT_COLOR_ID, 0);

	// Set material that will be used for this mesh
	VMaterial* material = new VMaterial();
	material->SetShader(Shader);
	MeshRenderer->SetMaterial(material);

	VFilePath fp("Textures/test.png", FILE_EDITOR_RESOURCE_DIRECTORY);
	VFilePath fp2("Textures/test2.png", FILE_EDITOR_RESOURCE_DIRECTORY);

	Texture = VTexture2D::FromFile(fp);
	Texture2 = VTexture2D::FromFile(fp2);

	material->AddTexture("tex1", Texture);
	material->AddTexture("tex2", Texture2);
	return true;
}

//THIS IS ALL TEST CODE FOR NOW
void VEngine::Render()
{
	Shader->Use();

	MeshRenderer->Render();

}