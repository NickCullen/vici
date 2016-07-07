#pragma once

// Type of value in an element
enum EElementType
{
	ELEM_TYPE_FLOAT,
	ELEM_TYPE_DOUBLE,

	ELEM_TYPE_INT8,
	ELEM_TYPE_INT16,
	ELEM_TYPE_INT24,
	ELEM_TYPE_INT32,

	ELEM_TYPE_UINT8,
	ELEM_TYPE_UINT16,
	ELEM_TYPE_UINT24,
	ELEM_TYPE_UINT32,
};

enum EColorMode
{
	COLOR_GREYSCALE,		// 1 component
	COLOR_GREY_ALPHA,		// 2 Component
	COLOR_RGB,				// 3 component
	COLOR_RGBA				// 4 component
};

/**
* Defines how the texture is used by the graphics library
*/
enum ETextureType
{
	TEXTURE_1D,
	TEXTURE_2D,
	TEXTURE_3D
};

/**
* Defines what happens when coordinates exceed 0 <-> 1
*/
enum ETextureWrapMode
{
	WRAP_REPEAT,
	WRAP_MIRRORED_REPEAT,
	WRAP_CLAMP_TO_EDGE,
	WRAP_CLAMP_TO_BORDER
};

/**
* Filter methods for textures
*/
enum ETextureFilterMethod
{
	FILTER_NEAREST,			// Returns the pixel that is closest to the coordinates.
	FILTER_LINEAR,			// Returns the weighted average of the 4 pixels surrounding the given coordinates.

	// Sample from mipmaps instead
	FILTER_NEAREST_MIPMAP_NEAREST,
	FILTER_LINEAR_MIPMAP_NEAREST,
	FILTER_NEAREST_MIPMAP_LINEAR,
	FILTER_LINEAR_MIPMAP_LINEAR
};