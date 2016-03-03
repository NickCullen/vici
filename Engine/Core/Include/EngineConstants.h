#pragma once

// Max number of rendering contexts
#ifdef GLEW_MX
static const int MAX_RENDER_CONTEXTS = 64;
// Will always be 1 if standalone game
#else
static const int MAX_RENDER_CONTEXTS = 1;
#endif

// Max number of elements per vertex in a vertex buffer
static const int MAX_ELEMENTS_PER_VERTEX = 16;