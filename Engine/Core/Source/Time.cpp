#include "Time.h"

#ifdef VICI_WINDOWS
#include <Windows.h>

#define GetTimeInSeconds() GetTickCount() / 1000.0f

#endif


VTime::VTime()
	:VSingleton(this)
{

}
void VTime::UpdateTime()
{
	Time = (float)GetTimeInSeconds();
}