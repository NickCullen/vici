#pragma once

#ifdef Platform_EXPORTS
#ifdef VICI_WINDOWS
#define PLATFORM_API __declspec(dllexport)
#else
#define PLATFORM_API
#endif
#else
#ifdef VICI_WINDOWS
#define PLATFORM_API __declspec(dllimport)
#else
#define PLATFORM_API
#endif
#endif