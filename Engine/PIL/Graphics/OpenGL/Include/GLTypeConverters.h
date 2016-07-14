#pragma once

#include "PIL/PILAPI.h"
#include "PIL/DataTypes/PlatformTypes.h"
#include "PIL/Graphics/GraphicsTypes.h"
#include "PIL/Graphics/OpenGL/Include/Glew.h"

#define CASE_TYPE(TYPE) case PlatformTypeToCode<TYPE>::Code: 

class PIL_API GLTypeConverter
{
public:

	static inline uint32 ElementTypeToGL(EPlatformType Type)
	{
		switch (Type)
		{
			CASE_TYPE(int8)		return GL_BYTE;
			CASE_TYPE(int16)	return GL_SHORT;
			CASE_TYPE(int32)	return GL_INT;
			CASE_TYPE(int64)	return GL_INT;				// Not Supported - GL_INT assumed

			CASE_TYPE(uint8)	return GL_UNSIGNED_BYTE;
			CASE_TYPE(uint16)	return GL_UNSIGNED_SHORT;
			CASE_TYPE(uint32)	return GL_UNSIGNED_INT;
			CASE_TYPE(uint64)	return GL_UNSIGNED_INT;		// not Supported - GL_UNSIGNED_INT assumed

			CASE_TYPE(float32)	return GL_FLOAT;	
			CASE_TYPE(float64)	return GL_DOUBLE;
			
			default: return GL_FLOAT;						// Default - Float assumed
		}
	}

	static inline uint32 ColorModeToGL(EColorMode colorMode)
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


	static inline uint32 TextureTypeToGL(ETextureType texType)
	{
		switch (texType)
		{
		case TEXTURE_1D: return GL_TEXTURE_1D;
		case TEXTURE_2D: return GL_TEXTURE_2D;
		case TEXTURE_3D: return GL_TEXTURE_3D;
		default:		 return GL_TEXTURE_2D;	// 2D texture assumed
		}
	}

	static inline uint32 WrapModeToGL(ETextureWrapMode mode)
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

	static inline uint32 FilterMethodToGL(ETextureFilterMethod method)
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

	static inline uint32 BufferTypeToGL(EBufferType Type)
	{
		switch (Type)
		{
		case ARRAY_BUFFER:		return GL_ARRAY_BUFFER;
		case ELEMENT_BUFFER:	return GL_ELEMENT_ARRAY_BUFFER;
		default:				return GL_ARRAY_BUFFER;		// Assume array buffer
		}
	}

	static inline uint32 BufferUsageToGL(EBufferUse Usage)
	{
		switch (Usage)
		{
		case STATIC_DRAW:		return GL_STATIC_DRAW;
		case DYNAMIC_DRAW:		return GL_DYNAMIC_DRAW;
		case STREAM_DRAW:		return GL_STREAM_DRAW;
		default:				return GL_STATIC_DRAW;	// Assume static
		}
	}

	static inline uint32 IndexTypeToGL(EIndexType IndexType)
	{
		switch (IndexType)
		{
		case INDEX_TYPE_POINTS:				return GL_POINTS;
		case INDEX_TYPE_LINES: 				return GL_LINES;
		case INDEX_TYPE_LINE_LOOP:			return GL_LINE_LOOP;
		case INDEX_TYPE_LINE_STRIP:			return GL_LINE_STRIP;
		case INDEX_TYPE_TRIANGLES:			return GL_TRIANGLES;
		case INDEX_TYPE_TRIANGLE_STRIP:		return GL_TRIANGLE_STRIP;
		case INDEX_TYPE_TRIANGLE_FAN:		return GL_TRIANGLE_FAN;
		case INDEX_TYPE_QUADS:				return GL_QUADS;
		case INDEX_TYPE_QUAD_STRIP:			return GL_QUAD_STRIP;
		case INDEX_TYPE_POLYGON:			return GL_POLYGON;
		default:							return GL_TRIANGLES;	// Assume triangles
		}
	}
};