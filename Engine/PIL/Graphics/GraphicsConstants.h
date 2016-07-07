#pragma once

#include "PIL/DataTypes/PlatformTypes.h"

#ifdef VICI_EDITOR
static const uint32 MAX_RENDER_CONTEXTS = 32;
#else
static const uint32 MAX_RENDER_CONTEXTS = 1;
#endif

static const uint32 MAX_ELEMENTS_PER_VERTEX = 8;