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
	ELEM_TYPE_INT,
	ELEM_TYPE_UNSIGNED_INT
};

enum EColorMode
{
	COLOR_RGB,
	COLOR_RGBA
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