#include <stdio.h>
#include "Input.h"
#include "Engine.h"
#include "Renderer.h"
#include "FilePath.h"
#include "Environment.h"
#include "MathLib.h"
#include "Window.h"
#include <random>
#include <time.h>




void Test()
{
	
	VEngine::Register();
	VHash::Register();
	
	for (size_t i = 0; i < ponder::classCount(); i++)
	{
		const ponder::Class& cl = ponder::classByIndex(i);

		printf("Stats for class %s:\n", cl.name().c_str());
		printf("\tBase class = %s\n", cl.baseCount() > 0 ? cl.base(0).name().c_str() : "none");
		printf("\t%d Constructors\n", cl.constructorCount());
		printf("\t%d Properties\n", cl.propertyCount());
		printf("\t%d Methods\n", cl.functionCount());
		
		
	}
	

}

// Main
int main(int argc, char** argv)
{
	srand((unsigned int)time(NULL));
	
	VWindow win;
	win.SetSize(512, 512);
	win.SetTitle("My Window");
	win.SetMode(EWindowMode::WINDOW_DEFAULT_NO_TOPBAR);
	if (!win.CreateNewWindow())
	{
		printf("Leaving\n");
	}


	// Setup stuff
	VString vpath = VEnvironment::GetSystemEnvVar("VICI_HOME");
	VFilePath vResPath = vpath + "Resources/";

	printf("Res = %s\n", (char*)vResPath);
	VEnvironment::GetInstance()->Put(ItemToString(FILE_EDITOR_DIRECTORY), vpath.c_str());
	VEnvironment::GetInstance()->Put(ItemToString(FILE_EDITOR_RESOURCE_DIRECTORY), vResPath);

	VEngine* vici = new VEngine();
	vici->Init(0, nullptr);

	Test();

	uint32 frame = 0;

	int curMode = WINDOW_DEFAULT_NO_TOPBAR;

	while (!win.ShouldClose())
	{
		// Per frame init
		frame++;
		vici->SetCurrentFrame(frame);

		win.MakeCurrent();

		VRenderer::GetInstance()->SetViewport(0, 0, win.GetWidth(), win.GetHeight());
		VRenderer::GetInstance()->ClearAllBuffers();

		win.PollEvents();

		vici->Update();
		vici->Render();

		win.Swapbuffers();


		if (VInput::GetInstance()->KeyDown(KEY_M))
		{
			curMode++;
			if (curMode > EWindowMode::WINDOW_FULLSCREEN_BORDERLESS)
				curMode = 0;
			
			win.SetMode((EWindowMode)curMode);
		}
		else if (VInput::GetInstance()->KeyUp(KEY_4))
			printf("4 released\n");
		else if (VInput::GetInstance()->Key(KEY_4))
			printf("4 held\n");
	}

	return 0;
}