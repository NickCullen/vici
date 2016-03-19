#include "Environment.h"
#include <stdlib.h>	//Get env
#include <stdio.h>

VEnvironment::VEnvironment()
	:VSingleton(this)
{

}

VEnvironment::~VEnvironment()
{

}

void VEnvironment::Put(VHash key, const char* val, bool overwrite)
{
	Vars.Insert(key, val);
}

bool VEnvironment::Get(VHash key, VString& outVal)
{
	return Vars.Get(key, outVal);
}

bool VEnvironment::Remove(VHash key)
{
	return Vars.Remove(key);
}

VString VEnvironment::GetSystemEnvVar(const char* key)
{
	return getenv(key);
}
