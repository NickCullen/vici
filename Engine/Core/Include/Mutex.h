#pragma once

// VMutex is bassed on C++11 mutex
#include "CoreAPI.h"
#include <mutex>

// Export interface
class CORE_API std::mutex;

// typedef it to be more suitable to our standard
typedef std::mutex VMutex;

