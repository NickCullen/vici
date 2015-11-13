#include "APIDefinition.h"

#ifdef Core_EXPORTS
#define CORE_API DEFINE_API_EXPORT
#else
#define CORE_API DEFINE_API_IMPORT
#endif