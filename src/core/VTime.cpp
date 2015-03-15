#include "VTime.h"

VTime::VTime() : Singleton<VTime>(this)
{
	_time = _delta_time = 0.0f;
	_time_scale = 1.0f;
}

VTime::~VTime()
{

}