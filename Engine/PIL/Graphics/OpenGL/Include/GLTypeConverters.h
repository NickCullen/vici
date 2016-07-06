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
};