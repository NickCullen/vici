#include "PIL/Graphics/Texture.h"
#include "PIL/Graphics/OpenGL/Include/Glew.h"
#include <memory>
#include "PIL/Graphics/Renderer.h"
#include "PIL/Graphics/Shader.h"
#include "PIL/Graphics/OpenGL/Include/GLTypeConverters.h"

//REMEMBER: OpenGL textures (0,0) == bottom left and (1,1) == top right.

int32 VTexture::ActiveTextureCount = 0;

// Handle definition
struct VInternalTextureHandle
{
	GLuint Texture;
};

VTexture::VTexture(ETextureType type, ETextureWrapMode wrapMode)
	:Type(type),
	WrapMode(wrapMode),
	Pixels(nullptr),
	GenerateMipMap(true),
	MinFilterMethod(FILTER_LINEAR),
	MagFilterMethod(FILTER_LINEAR),
	LOD(0),
	InternalFormat(COLOR_RGB),
	PixelFormat(COLOR_RGB),
	PixelDataType(TYPE_UINT8)
{
	Handle = new VInternalTextureHandle();
	Handle->Texture = 0;
}

VTexture::~VTexture()
{
	Flush();
	delete(Handle);
}

void VTexture::Bind(int32 activeTextureNum)
{
	glActiveTexture(GL_TEXTURE0 + activeTextureNum);
	glBindTexture(GLTypeConverter::TextureTypeToGL(Type), Handle->Texture);
}

void VTexture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE0);
}

bool VTexture::Lock()
{
	FlushGPUMemory();
	glGenTextures(1, &Handle->Texture);

	// Error generating texture
	if (Handle->Texture <= 0)
		return false;

	glBindTexture(GLTypeConverter::TextureTypeToGL(Type), Handle->Texture);

	return true;
}

void VTexture::FlushClientMemory()
{
	if (Pixels != nullptr)
	{
		delete[] Pixels;
		Pixels = nullptr;
	}
}

void VTexture::FlushGPUMemory()
{
	if (Handle->Texture > 0)
	{
		glDeleteTextures(1, &Handle->Texture);
		Handle->Texture = 0;
	}
}

void VTexture::Flush()
{
	FlushGPUMemory();
	FlushClientMemory();
}

void VTexture::SetBorderColor(const Vector4f& color)
{
	Bind();	// Ensure bound
	float* floatData = (float*)&color;
	glTexParameterfv(GLTypeConverter::TextureTypeToGL(Type), GL_TEXTURE_BORDER_COLOR, floatData);
}

void VTexture::SetMinFilterMetho(ETextureFilterMethod method)
{
	MinFilterMethod = method;
}
void VTexture::SetMagFilterMetho(ETextureFilterMethod method)
{
	MagFilterMethod = method;
}

void VTexture::FromArray(void* pixels, int32 sizeInBytes)
{
	FlushClientMemory();
	Pixels = (void*)new uint8[sizeInBytes];
	memcpy(Pixels, pixels, sizeInBytes);
}

EColorMode VTexture::ComponentCountToColorMode(int8 count)
{
	switch (count)
	{
		case 1:		return COLOR_GREYSCALE;
		case 2:		return COLOR_GREY_ALPHA;
		case 3:		return COLOR_RGB;
		case 4:		return COLOR_RGBA;
		default:	return COLOR_RGB;	// Assume rgb
	}
}

int8 VTexture::ComponentsInColorMode(EColorMode mode)
{
	switch (mode)
	{
	case COLOR_GREYSCALE:	return 1;
	case COLOR_GREY_ALPHA:	return 2;
	case COLOR_RGB:			return 3;
	case COLOR_RGBA:		return 4;
	default:				return 3;		// Assume rgb
	}
}

int8 VTexture::ComponentsInColorMode()
{
	return ComponentsInColorMode(PixelFormat);
}

bool VTexture::SendToShader(VShaderInputHandle* handle)
{
	Bind(ActiveTextureCount);
	glUniform1i(VShader::ShaderInputToGL(handle), ActiveTextureCount);
	ActiveTextureCount++;
	return true;	// TEMP
}

void VTexture::CleanupFromShader()
{
	ActiveTextureCount--;
}

