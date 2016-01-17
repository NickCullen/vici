#include "APIDefinition.h"

#ifdef Math_EXPORTS
#define MATH_API DEFINE_API_EXPORT
#else
#define MATH_API DEFINE_API_IMPORT
#endif