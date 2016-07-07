#ifdef VICI_WINDOWS
#define API_EXPORT __declspec(dllexport)
#define API_IMPORT __declspec(dllimport)
#else
#define API_EXPORT 
#define API_IMPORT 
#endif

#ifdef ViciEditor_EXPORTS
#define VICI_EDITOR_API API_EXPORT
#ifndef EXPIMP_TEMPLATE
#define EXPIMP_TEMPLATE
#endif
#else
#define VICI_EDITOR_API API_IMPORT
#ifndef EXPIMP_TEMPLATE
#define EXPIMP_TEMPLATE extern
#endif
#endif