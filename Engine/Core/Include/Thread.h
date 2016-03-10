#pragma once

// VThread is bassed on C++11 threads
#include "CoreAPI.h"
#include <thread>

// Export interface
class CORE_API std::thread;

// typedef it to be more suitable to our standard
typedef std::thread VThread;


