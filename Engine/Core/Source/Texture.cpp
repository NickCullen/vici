#include "Texture.h"
#include "Glew.h"
#include "Vector4.h"
#include <memory>
#include "Renderer.h"
//REMEMBER: OpenGL textures (0,0) == bottom left and (1,1) == top right.

int32 VTexture::ActiveTextureCount = 0;

VTexture::VTexture(ETextureType type, ETextureWrapMode wrapMode)
	:Type(type),
	WrapMode(wrapMode),
	Handle(0),
	Pixels(nullptr),
	GenerateMipMap(true),
	MinFilterMethod(FILTER_LINEAR),
	MagFilterMethod(FILTER_LINEAR),
	LOD(0),
	InternalFormat(COLOR_RGB),
	PixelFormat(COLOR_RGB),
	PixelDataType(ELEM_TYPE_UINT8)
{
}

VTexture::~VTexture()
{
	Flush();
}

uint32 VTexture::TextureTypeToGL(const ETextureType texType)
{
	switch (texType)
	{
		case TEXTURE_1D: return GL_TEXTURE_1D;
		case TEXTURE_2D: return GL_TEXTURE_2D;
		case TEXTURE_3D: return GL_TEXTURE_3D;
		default:		 return GL_TEXTURE_2D;	// 2D texture assumed
	}
}

uint32 VTexture::WrapModeToGL(const ETextureWrapMode mode)
{
	switch (mode)
	{
		case WRAP_REPEAT:				return GL_REPEAT;
		case WRAP_MIRRORED_REPEAT:		return GL_MIRRORED_REPEAT;
		case WRAP_CLAMP_TO_EDGE:		return GL_CLAMP_TO_EDGE;
		case WRAP_CLAMP_TO_BORDER:		return GL_CLAMP_TO_BORDER;
		default:						return GL_REPEAT;		// Assume repeat
	}
}

uint32 VTexture::FilterMethodToGL(const ETextureFilterMethod method)
{
	switch (method)
	{
		case FILTER_NEAREST:				return GL_NEAREST;
		case FILTER_LINEAR:					return GL_LINEAR;
		case FILTER_NEAREST_MIPMAP_NEAREST:	return GL_NEAREST_MIPMAP_NEAREST;
		case FILTER_LINEAR_MIPMAP_NEAREST:	return GL_LINEAR_MIPMAP_NEAREST;
		case FILTER_NEAREST_MIPMAP_LINEAR:	return GL_NEAREST_MIPMAP_LINEAR;
		case FILTER_LINEAR_MIPMAP_LINEAR:	return GL_LINEAR_MIPMAP_LINEAR;
		default:							return GL_LINEAR;	// Assume linear
	}
}

void VTexture::Bind(int32 activeTextureNum)
{
	glActiveTexture(GL_TEXTURE0 + activeTextureNum);
	glBindTexture(TextureTypeToGL(Type), Handle);
}

void VTexture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE0);
}

bool VTexture::Lock()
{
	FlushGPUMemory();
	glGenTextures(1, &Handle);

	// Error generating texture
	if (Handle <= 0)
		return false;

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
	if (Handle > 0)
	{
		glDeleteTextures(1, &Handle);
		Handle = 0;
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
	glTexParameterfv(TextureTypeToGL(Type), GL_TEXTURE_BORDER_COLOR, floatData);
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
	VRenderer::GetInstance()->BindUniform(handle, ActiveTextureCount);
	ActiveTextureCount++;
	return true;	// TEMP
}

void VTexture::CleanupFromShader()
{
	ActiveTextureCount--;
}