#include "APIDefinition.h"

#ifdef Assets_EXPORTS
#define ASSETS_API DEFINE_API_EXPORT
#else
#define ASSETS_API DEFINE_API_IMPORT
#endif
