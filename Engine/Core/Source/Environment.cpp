#include "Environment.h"
#include <stdlib.h>	//Get env
#include <stdio.h>

VEnvironment::VEnvironment()
	:VSingleton(this),
	Head(nullptr)
{

}

VEnvironment::~VEnvironment()
{

}

bool VEnvironment::Put(VHash key, const char* val, bool overwrite)
{
	VEnvVar* newVar = Head;
	if (Head != nullptr)
	{
		while (newVar)
		{
			// Variable already exists
			if (newVar->Key == key)
			{
				// If we have set it to overwrite then we can simple break
				// and set value
				if (overwrite)
					break;
				// Else we are not allowed to overrwrite so return false
				else
					return false;
			}
			
			// New entry
			else if (newVar->Next == nullptr)
			{
				newVar->Next = new VEnvVar();
				newVar = newVar->Next;
				break;
			}

			// Search next
			else
				newVar = newVar->Next;
			
		}
	}
	// Simple alloc
	else
	{
		newVar = Head = new VEnvVar();
		newVar->Next = nullptr;
	}

	// if we got this far then we must update the variable
	if (newVar)
	{
		newVar->Key = key;
		newVar->Value = val;

		return true;
	}

	return false;
}

const char* VEnvironment::Get(VHash key)
{
	VEnvVar* current = Head;
	while (current)
	{
		if (current->Key == key)
			return current->Value.c_str();
		else
			current = current->Next;
	}
	return nullptr;
}

bool VEnvironment::Remove(VHash key)
{
	VEnvVar* current = Head;
	VEnvVar* previous = nullptr;
	while (current)
	{
		if (current->Key == key)
		{
			// Not at the head of the list	
			if (previous)
			{
				previous->Next = current->Next;
				delete(current);
				return true;
			}

			// we are at the head of the list
			else
			{
				Head = current->Next;
				delete(current);
				return true;
			}
		}
		else
		{
			previous = current;
			current = current->Next;
		}
	}
	return false;
}

const char* VEnvironment::GetSystemEnvVar(const char* key)
{
	return getenv(key);
}

void VEnvironment::PrintEnvVars()
{
	VEnvVar* current = Head;
	while (current)
	{
		printf("Key = %d, Val = %s\n", current->Key.Value(), current->Value.c_str());
		current = current->Next;
	}
}