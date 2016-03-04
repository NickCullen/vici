#include "VTypes.h"
#include "Glew.h"

uint32 VTypeConverter::ElementTypeToGL(const EElementType type)
{
	switch (type)
	{
		case ELEM_TYPE_FLOAT:			return GL_FLOAT;
		case ELEM_TYPE_INT:				return GL_INT;
		case ELEM_TYPE_UNSIGNED_INT:	return GL_UNSIGNED_INT;
		default:						return GL_FLOAT;	// Assume float
	}
}
uint32 VTypeConverter::ColorModeToGL(const EColorMode colorMode)
{
	switch (colorMode)
	{
		case COLOR_RGB:		return GL_RGB;
		case COLOR_RGBA:	return GL_RGBA;
		default:			return GL_RGB;	// Assume rgb
	}
}