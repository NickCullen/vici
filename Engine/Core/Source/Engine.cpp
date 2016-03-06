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
#include "Renderer.h"

VShader* Shader;
VMesh* Mesh1;
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

	Mesh1 = VPrimitiveShapes::CreateQuad();

	VFilePath vPath("Shaders\\test.vert", FILE_EDITOR_RESOURCE_DIRECTORY);
	VFilePath fPath("Shaders\\test.frag", FILE_EDITOR_RESOURCE_DIRECTORY);

	Shader = new VShader();
	Shader->Load(vPath, fPath);
	Shader->BindFragDataLocation(SHADER_OUT_COLOR_ID, 0);

	// Set shader that will be used to render mesh
	Mesh1->SetShader(Shader);

	VFilePath fp("Textures/test.png", FILE_EDITOR_RESOURCE_DIRECTORY);
	VFilePath fp2("Textures/test2.png", FILE_EDITOR_RESOURCE_DIRECTORY);

	Texture = VTexture2D::FromFile(fp);

	if (Texture->Lock())
	{
		for (int y = 0; y < Texture->GetHeight(); y += 2)
		{
			for (int x = 0; x < Texture->GetWidth(); x += 3)
				Texture->SetPixel(x, y, (y / (float)Texture->GetHeight()) * 255, 0, 0, 255);
		}
		Texture->Unlock();
	}
	Texture2 = VTexture2D::FromFile(fp2);

	return true;
}

//THIS IS ALL TEST CODE FOR NOW
void VEngine::Render()
{
	Shader->Use();

	UniformHandle tex1Handle = Shader->UniformLocation("tex1");
	Texture->Bind(0);
	glUniform1i(tex1Handle, 0);
	

	/*UniformHandle tex2Handle = Shader->UniformLocation("tex2");
	glUniform1i(tex2Handle, 1);
	Texture2->Bind(1);*/

	Mesh1->Render();

}