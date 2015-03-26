#include "TestProj.h"
#include "core.h"

TestProj::TestProj() : Project()
{
	_Platform->LogString("TestProj constructor\n");
}

TestProj::~TestProj()
{
	_Platform->LogString("TestProj destructor\n");
}

void TestProj::RegisterAssetImporters()
{
	_Platform->LogString("TestProj register asset importers\n");
}

void TestProj::RegisterComponents()
{
	_Platform->LogString("TestProj register components\n");
}