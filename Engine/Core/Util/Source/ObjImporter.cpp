#include "Core/Util/ObjImporter.h"
#include "PIL/Graphics/IndexBuffer.h"
#include "PIL/Graphics/VertexBuffer.h"

#define COMPARE(s1, s2) strcmp(s1, s2) == 0

OBJImporter::OBJImporter()
{

}

OBJImporter::~OBJImporter()
{

}

bool OBJImporter::Import(const VFilePath& file)
{
	VArray<Vector3f> positionsArr;
	VArray<Vector2f> uvArr;
	VArray<Vector3f> normalArr;
	VArray<Vector3f> paramArr;

	OBJObject* currentObject = nullptr;

	char buff[512];
	FILE* fp = fopen(file.GetString(), "r");

	if (fp)
	{
		// Parse data
		while (fscanf(fp, "%s", buff) > 0)
		{
			// Comment
			if (buff[0] == '#')
			{
				fgets(buff, sizeof(buff), fp);
				continue;
			}

			// Object name
			else if (buff[0] == 'o')
			{
				fscanf(fp, "%s", buff);

				currentObject = new OBJObject();
				currentObject->ReadableName = buff;

				Objects.push_back(currentObject);
			}

			// Vertex Position
			else if (COMPARE(buff, "v"))
			{
				Vector3f pos;
				fscanf(fp, "%f %f %f", &pos.x, &pos.y, &pos.z);
				positionsArr.push_back(pos);
			}

			// Vertex UV
			else if (COMPARE(buff, "vt"))
			{
				Vector2f uv;
				fscanf(fp, "%f %f", &uv.x, &uv.y);
				uvArr.push_back(uv);
			}

			// Vertex Normal
			else if (COMPARE(buff, "vn"))
			{
				Vector3f norm;
				fscanf(fp, "%f %f %f", &norm.x, &norm.y, &norm.z);
				normalArr.push_back(norm);
			}

			// Parameter space vertices
			else if (COMPARE(buff, "vp"))
			{
				Vector3f param;
				fscanf(fp, "%f %f %f", &param.x, &param.y, &param.z);
				paramArr.push_back(param);
			}

			// Face
			else if (COMPARE(buff, "f"))
			{
				uint32 val;	// Store the index
				char slash;
				int indexCount = 0;		// Number of indices per face (i.e. 3 == triangle, 4 == quad etc.)
				OBJFace face;

				do
				{
					// Position
					if (positionsArr.size() > 0)
					{
						fscanf(fp, "%d%c", &val, &slash);
						face.PosIndices.push_back(val-1);
					}

					// Normal
					if (normalArr.size() > 0)
					{
						fscanf(fp, "%d%c", &val, &slash);
						face.NormIndices.push_back(val-1);
					}

					// UV
					if (uvArr.size() > 0)
					{
						fscanf(fp, "%d%c", &val, &slash);
						face.UVIndices.push_back(val-1);
					}
					
					indexCount++;
				} while (slash != '\n');	// Loop through each face
				
				// Set appropriate index method
				switch (indexCount)
				{
					case 1:		face.Type = EIndexType::INDEX_TYPE_POINTS; break;
					case 2:		face.Type = EIndexType::INDEX_TYPE_LINES; break;
					case 3:		face.Type = EIndexType::INDEX_TYPE_TRIANGLES; break;
					case 4:		face.Type = EIndexType::INDEX_TYPE_QUADS; break;
					default:	face.Type = EIndexType::INDEX_TYPE_POLYGON; break;
				}

				face.IndexCount = indexCount;
				currentObject->Faces.push_back(face);
			}

			// Smooth group
			else if (COMPARE(buff, "s"))
			{
				fgets(buff, sizeof(buff), fp);  // Skip for now
				continue;
			}

			// Material file
			else if (COMPARE(buff, "mtllib"))
			{
				fscanf(fp, "%s", buff);	// Read the material filename
				ParseMaterialFile(file.GetDirectory(), buff);
			}

			// Use material
			else if (COMPARE(buff, "usemtl"))
			{
				fscanf(fp, "%s", buff);
				currentObject->Material = &Materials[buff];
			}
		}

		// Convert to interleaved vertex buffer
		VertexBuffer = new VVertexBuffer();

		int32 posIdx = positionsArr.size() > 0 ? VertexBuffer->AddElement<Vector3f>() : -1;
		int32 uvIdx = uvArr.size() > 0 ? VertexBuffer->AddElement<Vector2f>() : -1;
		int32 normalIdx = normalArr.size() > 0 ? VertexBuffer->AddElement<Vector3f>() : -1;
		int32 paramIdx = paramArr.size() > 0 ? VertexBuffer->AddElement<Vector3f>() : -1;

		if (VertexBuffer->Lock())
		{
			// Iterate over objects
			for (uint32 i = 0; i < Objects.size(); i++)
			{
				//OBJObject* o = Objects[i];
				OBJObject* o = Objects.at(i);

				// Iterate over objects faces
				for (uint32 j = 0; j < o->Faces.size(); j++)
				{
					//OBJFace* f = &o->Faces[j];
					OBJFace* f = &o->Faces.at(j);

					// Iterate over indices of the face
					for (uint32 k = 0; k < f->IndexCount; k++)
					{
						VertexBuffer->AddVertex();		// Add a vertex

						if (posIdx != -1) VertexBuffer->AddData<Vector3f>(positionsArr.at(f->PosIndices.at(k)), posIdx);
						if (uvIdx != -1) VertexBuffer->AddData<Vector2f>(uvArr.at(f->UVIndices.at(k)), uvIdx);
						if (normalIdx != -1) VertexBuffer->AddData<Vector3f>(normalArr.at(f->NormIndices.at(k)), normalIdx);
						//if (paramIdx != -1) VertexBuffer->AddData<Vector3f>(paramArr[f->para[k]], paramIdx);
					}
					

				}
			}

			VertexBuffer->Unlock();
		}
		fclose(fp);

		return true;
	}

	return false;
}

void OBJImporter::ParseMaterialFile(const VString& directory, const VString& mtline)
{
	VString fullPath = directory + mtline;

	char buff[512];
	FILE* fp = fopen(fullPath.c_str(), "r");

	VHash currentMaterialName;
	OBJMaterial currentMaterial;

	if (fp)
	{
		while (fscanf(fp, "%s", buff) > 0)
		{
			// Comment
			if (buff[0] == '#')
			{
				fgets(buff, sizeof(buff), fp);
				continue;
			}

			// New material
			else if (COMPARE(buff, "newmtl"))
			{
				fscanf(fp, "%s", buff);

				// If we are editing one already make sure its values are updated
				if (Materials.KeyExists(currentMaterialName))
				{
					Materials[currentMaterialName] = currentMaterial;
				}

				// New Material
				currentMaterialName = buff;
				currentMaterial.readableName = buff;
				Materials.Insert(currentMaterialName, currentMaterial);
				
			}

			// Specular pow
			else if (COMPARE(buff, "Ns"))
			{
				fscanf(fp, "%d", &currentMaterial.Ns);
			}

			// Ambient
			else if (COMPARE(buff, "Ka"))
			{
				fscanf(fp, "%f %f %f", &currentMaterial.Ka.x, &currentMaterial.Ka.y, &currentMaterial.Ka.z);
			}

			// Diffuse
			else if (COMPARE(buff, "Kd"))
			{
				fscanf(fp, "%f %f %f", &currentMaterial.Kd.x, &currentMaterial.Kd.y, &currentMaterial.Kd.z);
			}

			// Specular
			else if (COMPARE(buff, "Ks"))
			{
				fscanf(fp, "%f %f %f", &currentMaterial.Ks.x, &currentMaterial.Ks.y, &currentMaterial.Ks.z);
			}

			// Dissolve
			else if (buff[0] == 'd')
			{
				fscanf(fp, "%d", &currentMaterial.d);
			}
			
			// Lighting model
			else if (COMPARE(buff, "illum"))
			{
				fscanf(fp, "%d", &currentMaterial.illum);
			}

			// Ambient Map
			else if (COMPARE(buff, "map_Ka"))
			{
				fscanf(fp, "%s", buff);
				currentMaterial.map_Ka = buff;
			}

			// Diffuse Map
			else if (COMPARE(buff, "map_Kd"))
			{
				fscanf(fp, "%s", buff);
				currentMaterial.map_Kd = buff;
			}

			// Specular Map
			else if (COMPARE(buff, "map_Ks"))
			{
				fscanf(fp, "%s", buff);
				currentMaterial.map_Ks = buff;
			}

			// Specular Highlight Map
			else if (COMPARE(buff, "map_Ns"))
			{
				fscanf(fp, "%s", buff);
				currentMaterial.map_Ns = buff;
			}

			// Alpha Texturemap
			else if (COMPARE(buff, "map_d"))
			{
				fscanf(fp, "%s", buff);
				currentMaterial.map_d = buff;
			}

			// Bump Texturemap
			else if (COMPARE(buff, "bump") || COMPARE(buff, "map_bump"))
			{
				fscanf(fp, "%s", buff);
				currentMaterial.map_bump = buff;
			}

			// Displacement map
			else if (COMPARE(buff, "disp"))
			{
				fscanf(fp, "%s", buff);
				currentMaterial.disp = buff;
			}

			// Decal map
			else if (COMPARE(buff, "decal"))
			{
				fscanf(fp, "%s", buff);
				currentMaterial.decal = buff;
			}
		}

		// be sure to update last entry
		Materials[currentMaterialName] = currentMaterial;
	}
	
}