#include "APIDefinition.h"

#ifdef Util_EXPORTS
#define UTIL_API DEFINE_API_EXPORT
#else
#define UTIL_API DEFINE_API_IMPORT
#endif