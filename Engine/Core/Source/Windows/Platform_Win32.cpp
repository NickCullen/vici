#include "Platform.h"
#include "Vici.h"
#include "Display.h"
#include <stdio.h>
#include <direct.h>
#include "VTime.h"
#include <stdarg.h>
#include <SDL\SDL.h>


Platform::Platform() : Singleton<Platform>()
{
	Cwd[0] = '\0';
}

Platform::~Platform()
{

}

bool Platform::Init()
{
	if (SDL_Init(SDL_INIT_TIMER) < 0)
	{
		LogString("Could not initialize Timer\n");
		return false;
	}

	return true;
}

void Platform::LogString(const char* fmt, ...)
{
	  /* Write the error message */
	va_list args;
  	va_start (args, fmt);
  	vprintf (fmt, args);
  	va_end (args);
}

bool Platform::DeserializeEngineComponent(EngineSerializableComponent component, const char* datafile, void** opaque)
{
	std::string fullpath = datafile;
	_Platform->GetFullPath(fullpath);

	// Create the input stream
	CreateInputArchive(arch, inputStream, fullpath);

	// Deserialize
	switch (component)
	{
	case kDisplay:
		*opaque = new Display();

		_SERIALIZE_VAR_NAME(*(Display*)*opaque, "Display", arch);
		return true;
	default:
		return false;
	}

	return false;
}

uint32 Platform::GetTime()
{
	return SDL_GetTicks();
}

const char* Platform::Pathify(const char* file)
{
	char* start = (char*)file;
	while(*start != '\0')
	{
		if(*start == '/') *start = '\\';
		start++;
	}
	return file;
}

std::string& Platform::Pathify(std::string& file)
{
	char* start = (char*)(file.c_str());
	while (*start != '\0')
	{
		if (*start == '/') *start = '\\';
		start++;
	}
	return file;

}

std::string& Platform::GetFullPath(std::string& append)
{
	append = Cwd + append;
	return Pathify(append);
}
void Platform::SetCwd(const char* executable_path, bool trim_end)
{
	if(trim_end)
	{
		size_t back = strlen(executable_path);
		char* end = (char*)&executable_path[back];

		//loop backwards
		while(*--end != '\\')
			;

		//set zero-terminator
		*end = '\0';
	}

	//set cwd
	strcpy(Cwd, executable_path);
}