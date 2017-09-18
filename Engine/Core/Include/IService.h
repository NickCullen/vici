#pragma once

#include "Singleton.h"

/**
 * Interface base class for all services
 */
template<typename T>
class IService : public TSingleton<T>
{

};