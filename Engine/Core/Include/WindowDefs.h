#pragma once


// Don't expose underlying types
#define NativeWindow_t void*

// Foward decl
class VWindow;
class VButton;

// Callbacks ---
// Mouse button presses
typedef void(*Vmousebuttonfun)(VWindow* win, int, int, int);

// Called when cursor moves over the window
typedef void(*Vcursorposfun)(VWindow*, double, double);

typedef void(*Vcursorenterfun)(VWindow*, int);

typedef void(*Vscrollfun)(VWindow*, double, double);

typedef void(*Vkeyfun)(VWindow*, VButton* button);

typedef void(*Vcharfun)(VWindow*, unsigned int);

typedef void(*Vcharmodsfun)(VWindow*, unsigned int, int);

typedef void(*Vdropfun)(VWindow*, int, const char **);

