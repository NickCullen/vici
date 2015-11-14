#ifdef NDEBUG
#define VICI_RELEASE 1	// release build
#else
#define VICI_DEBUG 1	// debug build
#endif

#ifdef VICI_WINDOWS	// Windows specific includes
#include "glew.h"
#include <Windows.h>
#include "GLFW/glfw3.h"
#include <stdint.h>
#include <assert.h>

#ifdef VICI_DEBUG // Windows Debug includes
#include "vld.h"
#endif

typedef GLFWwindow VWindow; // Windows typedefs

#endif // End Windows specific includes

#ifdef VICI_MAC // Mac specific includes 

#ifdef VICI_OPENGL
#include "GLFW/glfw3.h"
#include "OpenGLDefinitions/OpenGLDefinitions.h"
#endif

#include <stdint.h>
#include <assert.h>

#endif // End Mac specific includes 

#include <string>

// Constants
#define BUFF_LEN 512

// Common typedefs 
typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;

