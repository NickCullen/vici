#pragma once

#include <stdint.h>
#include "CoreAPI.h"

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float float32;
typedef double float64;


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
 * Static class that is meant to convert above Enum types to respective
 * GLenums
 */
class CORE_API VTypeConverter
{
private:
	VTypeConverter() = default;
	~VTypeConverter() = default;

public:
	static uint32 ElementTypeToGL(const EElementType elemType);
	static uint32 ColorModeToGL(const EColorMode colorMode);
};

// Macros for simplicity
#define ElementTypeToGL(type) VTypeConverter::ElementTypeToGL(type)
#define ColorModeToGL(mode) VTypeConverter::ColorModeToGL(mode)