#pragma once

/**
 * Valid types recognised by the GPU
 */
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

/**
 * Valid colour modes
 */
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
* Defines what happens when uv-coordinates exceed 0 <-> 1
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

/**
* Enum specifying what data a VBuffer holds
*/
enum EBufferType
{
	ARRAY_BUFFER,			// vertex data
	ELEMENT_BUFFER			// index data
};

/**
* Defines how a VBuffer is to be used
*/
enum EBufferUse
{
	STATIC_DRAW,		// Upload once - draw many times
	DYNAMIC_DRAW,		// Changed from time to time but drawn many more times than that
	STREAM_DRAW			// Vertex data will change almost every frame
};

/**
* Defines what index type an index array
* draws its vertices
*/
enum EIndexType
{
	INDEX_TYPE_POINTS,
	INDEX_TYPE_LINES,
	INDEX_TYPE_LINE_LOOP,
	INDEX_TYPE_LINE_STRIP,
	INDEX_TYPE_TRIANGLES,
	INDEX_TYPE_TRIANGLE_STRIP,
	INDEX_TYPE_TRIANGLE_FAN,
	INDEX_TYPE_QUADS,
	INDEX_TYPE_QUAD_STRIP,
	INDEX_TYPE_POLYGON
};