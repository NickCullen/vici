#include "APIDefinition.h"

#ifdef Vici_EXPORTS
#define VICI_API DEFINE_API_EXPORT
#else
#define VICI_API DEFINE_API_IMPORT
#endif