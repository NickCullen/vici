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