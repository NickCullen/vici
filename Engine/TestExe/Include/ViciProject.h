#ifndef ViciProject_H
#define ViciProject_H

#include "Project.h"

class ViciProject : public Project
{
private:

public:
	ViciProject();

	~ViciProject();

	void RegisterAssetImporters();

	void RegisterComponents();
};

#endif