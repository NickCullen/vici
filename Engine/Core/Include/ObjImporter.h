#pragma once

#include "CoreAPI.h"
#include "IndexBuffer.h"
#include "VString.h"

class CORE_API OBJImporter
{
private:

	// Parses the material file line (mtlib <matfile.mtl)
	void ParseMaterialFile(const VString& directory, const VString& line);
public:
	OBJImporter();

	~OBJImporter();

	/**
	 * Starts the import process off an obj file
	 */
	bool Import(const class VFilePath& file);
};