#include "APIDefinition.h"

#ifdef Rendering_EXPORTS
#define RENDERING_API DEFINE_API_EXPORT
#else
#define RENDERING_API DEFINE_API_IMPORT
#endif