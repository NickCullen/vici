#pragma once

#include "CoreAPI.h"
#include "IndexBuffer.h"

class CORE_API OBJImporter
{
private:

	// Parses the material file line (mtlib <matfile.mtl)
	void ParseMaterialFile(const class VString& directory, const class VString& line);
public:
	OBJImporter();

	~OBJImporter();

	/**
	 * Starts the import process off an obj file
	 */
	bool Import(const class VFilePath& file);
};