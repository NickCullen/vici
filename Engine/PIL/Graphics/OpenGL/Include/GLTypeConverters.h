#pragma once

#include "PIL/PILAPI.h"
#include "PIL/DataTypes/PlatformTypes.h"
#include "PIL/Graphics/GraphicsTypes.h"
#include "PIL/Graphics/OpenGL/Include/Glew.h"

class PIL_API GLTypeConverter
{
public:

	static inline uint32 GLTypeConverter::ElementTypeToGL(const EElementType type)
	{

		switch (type)
		{
		case ELEM_TYPE_FLOAT:			return GL_FLOAT;
		case ELEM_TYPE_DOUBLE:			return GL_DOUBLE;

		case ELEM_TYPE_INT8:			return GL_BYTE;
		case ELEM_TYPE_INT16:			return GL_SHORT;
		case ELEM_TYPE_INT32:			return GL_INT;

		case ELEM_TYPE_UINT8:			return GL_UNSIGNED_BYTE;
		case ELEM_TYPE_UINT16:			return GL_UNSIGNED_SHORT;
		case ELEM_TYPE_UINT32:			return GL_UNSIGNED_INT;

		default:						return GL_FLOAT;	// Assume float
		}
	}

	static inline uint32 GLTypeConverter::ColorModeToGL(const EColorMode colorMode)
	{
		switch (colorMode)
		{
		case COLOR_GREYSCALE:	return GL_R;
		case COLOR_GREY_ALPHA:	return GL_RG;
		case COLOR_RGB:			return GL_RGB;
		case COLOR_RGBA:		return GL_RGBA;
		default:				return GL_RGB;	// Assume rgb
		}
	}


	static inline uint32 TextureTypeToGL(const ETextureType texType)
	{
		switch (texType)
		{
		case TEXTURE_1D: return GL_TEXTURE_1D;
		case TEXTURE_2D: return GL_TEXTURE_2D;
		case TEXTURE_3D: return GL_TEXTURE_3D;
		default:		 return GL_TEXTURE_2D;	// 2D texture assumed
		}
	}

	static inline uint32 WrapModeToGL(const ETextureWrapMode mode)
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

	static inline uint32 FilterMethodToGL(const ETextureFilterMethod method)
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
};