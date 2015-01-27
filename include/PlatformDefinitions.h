
/* Platform Specific Includes */

//windows
#ifdef VICI_WINDOWS
#include "glew.h"
#include <Windows.h>
#include <stdint.h>
#endif
//mac
#ifdef VICI_MAC
#include <OpenGL/GL.h>
#include <OpenGL/GLU.h>
#endif



/* Integer typedefs */
typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;



/* OpenGL Typedefs */
#ifdef VICI_OPENGL
#define VICI_COLOR_BUFFER_BIT GL_COLOR_BUFFER_BIT
#define VICI_DEPTH_BUFFER_BIT GL_DEPTH_BUFFER_BIT
#define VICI_ACCUM_BUFFER_BIT GL_ACCUM_BUFFER_BIT
#define VICI_STENCIL_BUFFER_BIT GL_STENCIL_BUFFER_BIT

#endif