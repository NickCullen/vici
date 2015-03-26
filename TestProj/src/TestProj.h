#ifndef TESTPROJ_H
#define TESTPROJ_H

#include "Project.h"

class TestProj : public Project
{
private:

public:
	TestProj();

	~TestProj();

	void Project_RegisterAssetImporters();

	void Project_RegisterComponents();
};

#endif