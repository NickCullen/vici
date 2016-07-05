#include "PIL/Platform/Environment.h"
#include <stdlib.h>	//Get env
#include <stdio.h>

// Static init
VEnvironment* VEnvironment::Instance = nullptr;

VEnvironment::VEnvironment()
{

}

VEnvironment::~VEnvironment()
{

}

VEnvironment* VEnvironment::GetInstance()
{
	if (Instance == nullptr)
		Instance = new VEnvironment();
	return Instance;
}

uint32 VEnvironment::HashString(const VString& str)
{
	uint32 hash = 2166136261;

	for each (char c in str)
	{
		hash ^= c;
		hash *= 16777619;
	}

	return hash;
}

void VEnvironment::Put(const VString& key, const char* val, bool overwrite)
{
	Vars.Insert(HashString(key), val);
}

bool VEnvironment::Get(const VString& key, VString& outVal)
{
	return Vars.Get(HashString(key), outVal);
}

bool VEnvironment::Remove(const VString& key)
{
	return Vars.Remove(HashString(key));
}

VString VEnvironment::GetSystemEnvVar(const char* key)
{
	return getenv(key);
}

EPlatform VEnvironment::GetPlatform()
{
	return PLATFORM_WIN32;
}
