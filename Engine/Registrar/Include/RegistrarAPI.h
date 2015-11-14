#include "APIDefinition.h"

#ifdef Registrar_EXPORTS
#define REGISTRAR_API DEFINE_API_EXPORT
#else
#define REGISTRAR_API DEFINE_API_IMPORT
#endif