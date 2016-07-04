#include "Renderer.h"
#include "Glew.h"
#include <stdio.h>
#include "Array.h"
#include "VertexBuffer.h"

// Static init
VRenderContext* VRenderer::CurrentContext = nullptr;

#pragma region - VRenderContext Definition -

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

#ifdef GLEW_MX
GLEWContext* glewGetContext()
{
	return VRenderer::GetInstance()->GetCurrentContext()->Context;
}
#endif


#pragma endregion

#pragma region - VShaderHandle definition -

struct VShaderInputHandle
{
	GLint GLLocationHandle;
};

struct VShaderHandle
{
	GLuint ProgramHandle;
	GLuint VertexHandle;
	GLuint GeomHandle;
	GLuint FragHandle;

	VArray<VShaderInputHandle*> Unforms;
	VArray<VShaderInputHandle*> Attributes;		// Per vertex attributes

	VShaderHandle()
		:ProgramHandle(0),
		VertexHandle(0),
		GeomHandle(0),
		FragHandle(0) {}
};

void DebugShader(GLuint shader, GLuint checkType)
{
	//check for errors
	int noError;
	glGetShaderiv(shader, checkType, &noError);
	if (!noError)
	{
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen>1)
		{
			char* infoLog = new char[infoLen];
			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			printf("Error in shader %d - %s\n", shader, infoLog);
			delete(infoLog);
		}
	}
}


void DebugProgram(GLuint program, GLuint checkType)
{
	//check for errors
	int noError;
	glGetProgramiv(program, checkType, &noError);
	if (!noError)
	{
		GLint infoLen = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen>1)
		{
			char* infoLog = new char[infoLen];
			glGetProgramInfoLog(program, infoLen, NULL, infoLog);
			printf("Error in program %d - %s\n", program, infoLog);
			delete(infoLog);
		}
	}
}


#pragma endregion


VRenderer::VRenderer() 
	:VSingleton(this),
	ActiveShader(nullptr)
{

}

VRenderer::~VRenderer()
{

}

#pragma region - Render Context Methods -

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


#pragma endregion

#pragma region - Shader methods - 

VShaderHandle* VRenderer::CreateShaderHandles(int mask)
{
	VShaderHandle* handle = new VShaderHandle();

	if (mask & SHADER_VERTEX)
		handle->VertexHandle = glCreateShader(GL_VERTEX_SHADER);
	if (mask & SHADER_GEOMETRY)
		handle->GeomHandle = glCreateShader(GL_GEOMETRY_SHADER);
	if (mask & SHADER_FRAGMENT)
		handle->FragHandle = glCreateShader(GL_FRAGMENT_SHADER);

	return handle;
}

void VRenderer::SetShaderSource(VShaderHandle* handle, EShaderType mask, char** source)
{
	if (mask & SHADER_VERTEX && handle->VertexHandle > 0)
		glShaderSource(handle->VertexHandle, 1, source, NULL);
	if (mask & SHADER_GEOMETRY && handle->GeomHandle > 0)
		glShaderSource(handle->GeomHandle, 1, source, NULL);
	if (mask & SHADER_FRAGMENT && handle->FragHandle > 0)
		glShaderSource(handle->FragHandle, 1, source, NULL);
}

void VRenderer::CompileShader(VShaderHandle* handle)
{
	//compile and check for errors
	if (handle->VertexHandle > 0)
	{
		glCompileShader(handle->VertexHandle);
		DebugShader(handle->VertexHandle, GL_COMPILE_STATUS);
	}
		
	if (handle->GeomHandle > 0)
	{
		glCompileShader(handle->GeomHandle);
		DebugShader(handle->GeomHandle, GL_COMPILE_STATUS);
	}

	if (handle->FragHandle > 0)
	{
		glCompileShader(handle->FragHandle);
		DebugShader(handle->FragHandle, GL_COMPILE_STATUS);
	}

	//create program and attach shaders
	handle->ProgramHandle = glCreateProgram();

	if (handle->VertexHandle > 0)
		glAttachShader(handle->ProgramHandle, handle->VertexHandle);

	if (handle->GeomHandle > 0)
		glAttachShader(handle->ProgramHandle, handle->GeomHandle);

	if (handle->FragHandle > 0)
		glAttachShader(handle->ProgramHandle, handle->FragHandle);

	//link the shaders to program and check for error
	glLinkProgram(handle->ProgramHandle);

	//print any errors
	DebugProgram(handle->ProgramHandle, GL_LINK_STATUS);
}

void VRenderer::DestroyShader(VShaderHandle* shader)
{
	if (shader->VertexHandle > 0)
		glDeleteShader(shader->VertexHandle);
	if (shader->FragHandle > 0)
		glDeleteShader(shader->GeomHandle);
	if (shader->FragHandle > 0)
		glDeleteShader(shader->FragHandle);
	if (shader->ProgramHandle > 0)
		glDeleteProgram(shader->ProgramHandle);
}

bool VRenderer::SetActiveShader(VShaderHandle* handle)
{
	if (handle->ProgramHandle > 0)
	{
		glUseProgram(handle->ProgramHandle);

		return true;
	}
	else
		return false;
}

void VRenderer::BindFragDataLocation(VShaderHandle* shaderHanel, const char* id, uint32 location)
{
	glBindFragDataLocation(shaderHanel->ProgramHandle, location, id);
}

VShaderInputHandle* VRenderer::GetAttributeHandle(VShaderHandle* shader, const char* attribName)
{
	GLint loc = glGetAttribLocation(shader->ProgramHandle, attribName);
	if (loc == -1)
		return nullptr;

	// Create uniform handle and retrieve it
	for each (VShaderInputHandle* handle in shader->Attributes)
	{
		if (handle->GLLocationHandle == loc)
			return handle;
	}

	// If we got here this means we need to add it to the Uniforms list
	VShaderInputHandle* newHandle = new VShaderInputHandle();
	newHandle->GLLocationHandle = loc;

	shader->Attributes.push_back(newHandle);

	return newHandle;
}

VShaderInputHandle* VRenderer::GetUniformHandle(VShaderHandle* shader, const char* uniformName)
{
	// First ensure it actually exists
	GLint loc = glGetUniformLocation(shader->ProgramHandle, uniformName);
	if (loc == -1)
		return nullptr;

	// Create uniform handle and retrieve it
	for each (VShaderInputHandle* handle in shader->Unforms)
	{
		if (handle->GLLocationHandle == loc)
			return handle;
	}

	// If we got here this means we need to add it to the Uniforms list
	VShaderInputHandle* newHandle = new VShaderInputHandle();
	newHandle->GLLocationHandle = loc;
	
	shader->Unforms.push_back(newHandle);

	return newHandle;
}

VShaderInputHandle* VRenderer::GetSamplerHandle(VShaderHandle* shader, const char* samplerName)
{
	return GetUniformHandle(shader, samplerName);	// Basically a uniform...
}

#pragma endregion


#pragma region - Vertex manipulation -

void VRenderer::EnableVertexAttribArray(VShaderInputHandle* attributeArrayHandle)
{
	glEnableVertexAttribArray(attributeArrayHandle->GLLocationHandle);
}

void VRenderer::VertexAttribPointer(VShaderInputHandle* attribArrayHandle, const VVertexElement* vertexElement, int32 vertexSize)
{
	glVertexAttribPointer(attribArrayHandle->GLLocationHandle,
		vertexElement->Info.NumOfComponents,
		ElementTypeToGL(vertexElement->Info.Type),
		vertexElement->Info.Normalize ? GL_TRUE : GL_FALSE,
		vertexSize,
		(void*)vertexElement->Offset);
}

#pragma endregion


#pragma region - Uniform manipulation - 

void VRenderer::BindUniform(VShaderInputHandle* handle, int32 uniform)
{
	glUniform1i(handle->GLLocationHandle, uniform);
}
#pragma endregion

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
