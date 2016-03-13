

#ifdef VICI_WINDOWS
#define API_EXPORT __declspec(dllexport)
#define API_IMPORT __declspec(dllimport)
#else
#define API_EXPORT 
#define API_IMPORT 
#endif

#ifdef CORE_EXPORTS
#define CORE_API API_EXPORT
#define EXPIMP_TEMPLATE
#else
#define CORE_API API_IMPORT
#define EXPIMP_TEMPLATE extern
#endif