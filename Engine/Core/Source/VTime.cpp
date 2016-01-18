#include "VTime.h"

VTime::VTime() : Singleton<VTime>()
{
	Time = DeltaTime = 0.0f;
	TimeScale = 1.0f;
}

VTime::~VTime()
{

}