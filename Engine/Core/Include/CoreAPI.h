#pragma once

#ifdef Core_EXPORTS
	#ifdef VICI_WINDOWS
		#define CORE_API __declspec(dllexport)
	#else
		#define CORE_API
	#endif
#else
	#ifdef VICI_WINDOWS
		#define CORE_API __declspec(dllimport)
	#else
		#define CORE_API
	#endif
#endif