#include "Logger.h"
#include "Platform.h"
#include <stdarg.h>

Logger::Logger() : Singleton<Logger>()
{

}

Logger::~Logger()
{

}

void Logger::Log(const char* fmt, ...)
{
#ifdef VICI_DEBUG
	//Platform_LogString(fmt, ...);
#endif
}