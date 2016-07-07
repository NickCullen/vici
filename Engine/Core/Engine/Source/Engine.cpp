#include "Core/Engine/Engine.h"
#include "PIL/Graphics/Renderer.h"
#include <stdio.h>

// Temp
#include "PIL/Graphics/Shader.h"
#include "Core/Graphics/MeshRenderer.h"
#include "Core/Graphics/PrimitiveShapes.h"
#include "PIL/Graphics/Texture2D.h"
#include "Core/Math/Math/Include/Vector4.h"
#include "PIL/FileSystem/FilePath.h"
#include "Core/Graphics/Material.h"

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
	MeshRenderer = new VMeshRenderer();
	MeshRenderer->SetMeshData(VPrimitiveShapes::CreateQuad());

	VFilePath shaderPath("Shaders\\test", FILE_EDITOR_RESOURCE_DIRECTORY);

	Shader = new VShader();
	Shader->Load(shaderPath);
	Shader->BindFragDataLocation(SHADER_OUT_COLOR_ID, 0);

	// Set material that will be used for this mesh
	VMaterial* material = new VMaterial();
	material->SetShader(Shader);
	MeshRenderer->SetMaterial(material);

	VFilePath fp("Textures/test.png", FILE_EDITOR_RESOURCE_DIRECTORY);
	VFilePath fp2("Textures/test2.png", FILE_EDITOR_RESOURCE_DIRECTORY);

	Texture = VTexture2D::FromFile(fp);
	Texture2 = VTexture2D::FromFile(fp2);

	material->AddParam("tex1", Texture);
	material->AddParam("tex2", Texture2);
	return true;
}

void VEngine::FixedUpdate()
{

}

void VEngine::Update()
{

}

//THIS IS ALL TEST CODE FOR NOW
void VEngine::Render()
{
	MeshRenderer->Render();
}
