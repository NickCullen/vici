#pragma once

#include "CoreAPI.h"
#include "IndexBuffer.h"
#include "VString.h"

#include "Dictionary.h"
#include "Vector3.h"

class CORE_API OBJImporter
{
	struct OBJMaterial
	{
		int32 Ns;
		int32 d;
		int32 illum;

		Vector3f Ka;
		Vector3f Kd;
		Vector3f Ks;
		
		VString map_Ka;
		VString map_Kd;
		VString map_Ks;
		VString map_Ns;
		VString map_d;
		VString map_bump;
		VString disp;		// Displacment map
		VString decal;		// Decal map
	};
private:
	VDictionary<OBJMaterial> Materials;	// Materials stored by their id

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