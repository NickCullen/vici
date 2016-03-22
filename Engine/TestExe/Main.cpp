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
	Vector3f v1(1, 2, 3);
	Vector4f v2(1, 2, 3, 4);

	Quaternion q;
	Quaternion q1(1, 2, 3, 4);
	Quaternion q2 = v1;
	Quaternion q3 = v2;


	q1.Normalize();
	q2.Normalize();

	float d = q1.Dot(q2);

	Quaternion rot = Quaternion::EulerAngles(0, 90, 0);
	
	Matrix3f m3 = rot;
	Matrix4f m4 = rot;


}

// Main
int main(int argc, char** argv)
{
	srand(time(NULL));
	
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