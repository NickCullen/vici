#pragma once

#ifdef Engine_EXPORTS
#ifdef VICI_WINDOWS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API
#endif
#else
#ifdef VICI_WINDOWS
#define ENGINE_API __declspec(dllimport)
#else
#define ENGINE_API
#endif
#endif