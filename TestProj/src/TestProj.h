#ifndef TESTPROJ_H
#define TESTPROJ_H

#include "Project.h"

class TestProj : public Project
{
private:

public:
	TestProj();

	~TestProj();

	void RegisterAssetImporters();

	void RegisterComponents();
};

#endif