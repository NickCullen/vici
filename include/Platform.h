#ifndef PLATFORM_H
#define PLATFORM_H

#ifndef NULL
#define NULL 0
#endif

//gets the current working directory
char* Platform_Getcwd(char* buff, int len);

//gets the time in milliseconds
double Platform_GetTime();

//opens a window
bool Platform_OpenWindow(int w, int h, const char* title);

//enters game loop
void Platform_EnterLoop(class Vici* v);

#endif