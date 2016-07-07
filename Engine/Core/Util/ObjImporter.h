#pragma once

#include "Core/CoreAPI.h"
#include "Core/EngineIncludes.h"
#include "PIL/Graphics/IndexBuffer.h"

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

		VString readableName;	
	};

	struct OBJFace
	{
		VArray<uint32> PosIndices;
		VArray<uint32> NormIndices;
		VArray<uint32> UVIndices;
		uint32 IndexCount;		// Number of indices (relates to Type)
		EIndexType Type;		// Type of face (Triangle/Quad/Polygon etc.)
	};

	struct OBJObject
	{
		VArray<OBJFace> Faces;	// Faces in this object (contains indices into the vertex buffer)
		OBJMaterial* Material;			// The id into the Materials array this object uses


		VString ReadableName;	
	};

private:
	VDictionary<OBJMaterial, VHash> Materials;	// Materials stored by their id

	VArray<OBJObject*> Objects;		// Objects in this obj file 

	class VVertexBuffer* VertexBuffer;			// Vertex Buffer for objects

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