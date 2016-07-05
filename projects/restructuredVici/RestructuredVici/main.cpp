#include <stdio.h>
#include "PIL/Platform/Window.h"
#include "PIL/Timer/Time.h"
#include "PIL/Timer/Timer.h"
#include "PIL/Graphics/Renderer.h"
#include "PIL/Graphics/Shader.h"
#include "PIL/FileSystem/FilePath.h"
#include "PIL/Graphics/PrimitiveShapes.h"
#include "PIL/Graphics/MeshData.h"
#include "PIL/Platform/Environment.h"
#include "PIL/Graphics/MeshRenderer.h"
#include "PIL/Graphics/Material.h"
#include "PIL/Graphics/Texture2D.h"

int main(int argc, char** argv)
{
	/* Setup Environment */

	// 1: Set running directory
	const char* path = argv[0];
	VEnvironment::GetInstance()->Put(EPlatformToString(FILE_RUNNING_DIRECTORY), VFilePath::TrimPath((char*)path));

	// 2: Set engine home directory
	std::string vpath = VEnvironment::GetSystemEnvVar("VICI_HOME");
	VFilePath vResPath = vpath + "Resources/";

	VEnvironment::GetInstance()->Put(EPlatformToString(FILE_EDITOR_DIRECTORY), vpath.c_str());
	VEnvironment::GetInstance()->Put(EPlatformToString(FILE_EDITOR_RESOURCE_DIRECTORY), vResPath);
	
	// 3: Present Window
	VWindow* win = new VWindow();
	win->SetSize(1000, 500);
	win->SetTitle("Hello, again");
	win->SetMode(WINDOW_FULLSCREEN_WINDOWED);
	win->CreateNewWindow();
	
	// Create and load shader
	VShader* shader = new VShader();
	shader->Load(VFilePath("Shaders/test", FILE_EDITOR_RESOURCE_DIRECTORY));

	// Tell it where we want the output to be
	shader->BindFragDataLocation(SHADER_OUT_COLOR_ID, 0);

	// Create mesh renderer and assign it a primitive shape Mesh data
	VMeshRenderer* MeshRenderer = new VMeshRenderer();
	MeshRenderer->SetMeshData(VPrimitiveShapes::CreateQuad());

	// Create material, Assign a shader and tell the MeshRenderer to use this material
	VMaterial* material = new VMaterial();
	material->SetShader(shader);
	MeshRenderer->SetMaterial(material);

	// Load 2 Textures
	VFilePath fp("Textures/test.png", FILE_EDITOR_RESOURCE_DIRECTORY);
	VFilePath fp2("Textures/test2.png", FILE_EDITOR_RESOURCE_DIRECTORY);

	VTexture2D* Texture = VTexture2D::FromFile(fp);
	VTexture2D* Texture2 = VTexture2D::FromFile(fp2);

	// Set them in the material 
	material->AddParam("tex1", Texture);
	material->AddParam("tex2", Texture2);

	VTimer timer;
	timer.Begin();

	VTime::GetInstance()->UpdateTime();
	while (!win->ShouldClose())
	{
		win->MakeCurrent();
		win->PollEvents();

		VTime::GetInstance()->UpdateTime();
		
		uint32 w = 0, h = 0;
		win->GetWindowSize(&w, &h);

		VRenderer::GetInstance()->SetViewport(0, 0, w, h);
		VRenderer::GetInstance()->ClearAllBuffers();
		VRenderer::GetInstance()->ClearColor(0, 0, 0);


		MeshRenderer->Render();

		win->Swapbuffers();

		timer.Tick();
		printf("time = %.4f\n", timer.GetTimeInSeconds());
		if (timer.GetTimeInSeconds() > 5.0f)
		{
			timer.Reset();
		}

		CHECK_RENDERER_ERR;
	}

	delete(win);

	return 0;
}