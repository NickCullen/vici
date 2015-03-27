#include "ViciProject.h"
#include "core.h"

ViciProject::ViciProject() : Project()
{
	_Platform->LogString("ViciProject constructor\n");
}

ViciProject::~ViciProject()
{
	_Platform->LogString("ViciProject destructor\n");
}

void ViciProject::RegisterAssetImporters()
{
	_Platform->LogString("ViciProject register asset importers\n");
}

void ViciProject::RegisterComponents()
{
	_Platform->LogString("ViciProject register components\n");
}