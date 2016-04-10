#include "Renderer.h"
#include "Glew.h"
#include <stdio.h>

// Static init
VRenderContext* VRenderer::CurrentContext = nullptr;

#pragma region - VRenderTypes -

struct VRenderContext
{
#ifdef GLEW_MX
	static uint32 Count;	// Number of contexts
	uint32 ID;
	GLEWContext* Context;
#else
	const uint32 ID = 0;
#endif

};

uint32 VRenderContext::Count = 0;

#pragma endregion

#ifdef GLEW_MX
GLEWContext* glewGetContext()
{
	return VRenderer::GetInstance()->GetCurrentContext()->Context;
}
#endif

VRenderer::VRenderer() 
	:VSingleton(this),
	ActiveShader(nullptr)
{

}

VRenderer::~VRenderer()
{

}

VRenderContext* VRenderer::CreateContext()
{
	VRenderContext* ctx = new VRenderContext();

	CurrentContext = ctx;

#ifdef GLEW_MX
	ctx->Context = new GLEWContext();
	glewContextInit(ctx->Context);
	ctx->ID = ctx->Count++;
#endif

	if (glewInit() != GLEW_OK)
	{
		DestroyContext(ctx);
		ctx = nullptr;
	}
	return ctx;
}

void VRenderer::DestroyContext(VRenderContext* context)
{
	if (context)
	{
#ifdef GLEW_MX
		if (context->Context) delete(context->Context);
#endif
		delete(context);
	}
}

void VRenderer::SetCurrentContext(VRenderContext* context) 
{ 
	CurrentContext = context; 
}

uint32 VRenderer::GetContextID()
{
	return CurrentContext ? CurrentContext->ID : 0;
}

void VRenderer::GetVersionString(const char** str)
{
	*str = (const char*)glGetString(GL_VERSION);
}

void VRenderer::GetVersionNumber(int32* major, int32* minor)
{
	glGetIntegerv(GL_MAJOR_VERSION, major);
	glGetIntegerv(GL_MINOR_VERSION, minor);
}

void VRenderer::CheckErrors(const char* message)
{
	GLenum error = glGetError();
	while (error != GL_NO_ERROR)  // make sure we check all Error flags!
	{
		if (message != nullptr)
			printf("OpenGL ErrorID: %d\n\tUserMessage: %s\n", error, message);
		else
			printf("OpenGL ErrorID: %d\n", error);
		error = glGetError(); // get next error if any.
	}
}

void VRenderer::ClearColor(float32 r, float32 g, float32 b, float32 a)
{
	glClearColor(r, g, b, a);
}

void VRenderer::ClearColorBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void VRenderer::ClearDepthBuffer()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void VRenderer::ClearAllBuffers()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void VRenderer::SetViewport(int32 x, int32 y, int32 width, int32 height)
{
	glViewport(x, y, width, height);
}
