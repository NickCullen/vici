#include "APIDefinition.h"

#ifdef Singletons_EXPORTS
#define SINGLETONS_API DEFINE_API_EXPORT
#else
#define SINGLETONS_API DEFINE_API_IMPORT
#endif