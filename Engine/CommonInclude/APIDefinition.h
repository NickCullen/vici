
#ifdef VICI_WINDOWS
#	define DEFINE_API_IMPORT __declspec( dllimport )		
#else											
#  define DEFINE_API_IMPORT								
#endif					

#ifdef VICI_WINDOWS
#	define DEFINE_API_EXPORT __declspec( dllexport )		
#else											
#  define DEFINE_API_EXPORT								
#endif			