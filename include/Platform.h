#ifndef PLATFORM_H
#define PLATFORM_H

#ifndef NULL
#define NULL 0
#endif

#include "PlatformDefinitions.h"

//logs a string to the output method per ssystem
void Platform_LogString(const char* fmt, ...);

//gets the current working directory
char* Platform_Getcwd(char* buff, int len);

//gets the time in milliseconds
double Platform_GetTime();

//enters game loop
void Platform_EnterLoop(class Vici* v);

//makes all the slashes the correct way
const char* Platform_Pathify(const char* file);

#endif