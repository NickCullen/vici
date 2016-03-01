#pragma once


// Don't expose underlying types
#define NativeWindow_t void*

// Foward decl
class VWindow;
class VButton;
class VMouseButton;
class VMouseInfo;
class VScrollInfo;
class VFileDropInfo;

// Callbacks ---
// Mouse button presses
typedef void(*Vmousebuttonfun)(VWindow* win, VMouseButton* button);

// Called when cursor moves over the window
typedef void(*Vcursorposfun)(VWindow*, VMouseInfo* mouseInfo);

typedef void(*Vcursorenterfun)(VWindow*, bool);

typedef void(*Vscrollfun)(VWindow*, VScrollInfo* scrollInfo);

typedef void(*Vkeyfun)(VWindow*, VButton* button);

typedef void(*Vdropfun)(VWindow*, VFileDropInfo* info);

typedef void(*Vcharfun)(VWindow*, unsigned int);

typedef void(*Vcharmodsfun)(VWindow*, unsigned int, int);



