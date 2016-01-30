#include "VTime.h"
#include "Platform.h"

VTime::VTime() : Singleton<VTime>()
{
	DeltaTime = 0.0f;
	TimeScale = 1.0f;
}

VTime::~VTime()
{

}
uint32 VTime::GetTime()
{
	return _Platform->GetTime();
}