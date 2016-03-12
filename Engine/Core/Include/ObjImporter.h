#pragma once

#include "CoreAPI.h"

class CORE_API OBJImporter
{
private:

public:
	OBJImporter();

	~OBJImporter();

	/**
	 * Starts the import process off an obj file
	 */
	bool Import(const class VFilePath& file);
};