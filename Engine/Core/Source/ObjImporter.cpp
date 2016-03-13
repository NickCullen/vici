#include "ObjImporter.h"
#include "FilePath.h"
#include "VString.h"
#include "Vector3.h"
#include "Vector2.h"
#include <vector>
#include "Array.h"

#define COMPARE(s1, s2) strcmp(s1, s2) == 0

/**
 * Stores face info
 */
struct OBJFace
{
	std::vector<uint32> pos;
	std::vector<uint32> norm;
	std::vector<uint32> uv;
	EIndexType Type;		// Type of face
};

OBJImporter::OBJImporter()
{

}

OBJImporter::~OBJImporter()
{

}

bool OBJImporter::Import(const VFilePath& file)
{
	char buff[512];
	FILE* fp = fopen(file.GetString(), "r");
	
	VString objectName;
	
	VArray<Vector3f> positionsArr;
	VArray<Vector2f> uvArr;
	VArray<Vector3f> normalArr;
	VArray<Vector3f> paramArr;
	//VArray<OBJFace> faceArr;
	std::vector<OBJFace> faceArr;

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

			// Object name
			else if (buff[0] == 'o')
			{
				fscanf(fp, "%s", buff);
				objectName = buff;
			}

			// Vertex Position
			else if (COMPARE(buff, "v"))
			{
				Vector3f pos;
				fscanf(fp, "%f %f %f", &pos.x, &pos.y, &pos.z);
				positionsArr.Add(pos);
			}

			// Vertex UV
			else if (COMPARE(buff, "vt"))
			{
				Vector2f uv;
				fscanf(fp, "%f %f", &uv.x, &uv.y);
				uvArr.Add(uv);
			}

			// Vertex Normal
			else if (COMPARE(buff, "vn"))
			{
				Vector3f norm;
				fscanf(fp, "%f %f %f", &norm.x, &norm.y, &norm.z);
				normalArr.Add(norm);
			}

			// Parameter space vertices
			else if (COMPARE(buff, "vp"))
			{
				Vector3f param;
				fscanf(fp, "%f %f %f", &param.x, &param.y, &param.z);
				paramArr.Add(param);
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
					if (positionsArr.GetCount() > 0)
					{
						fscanf(fp, "%d%c", &val, &slash);
						face.pos.push_back(val);
					}

					// Normal
					if (normalArr.GetCount() > 0)
					{
						fscanf(fp, "%d%c", &val, &slash);
						face.norm.push_back(val);
					}

					// UV
					if (uvArr.GetCount() > 0)
					{
						fscanf(fp, "%d%c", &val, &slash);
						face.uv.push_back(val);
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

				faceArr.push_back(face);
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
		}

		fclose(fp);

		return true;
	}

	return false;
}

void OBJImporter::ParseMaterialFile(const VString& directory, const VString& mtline)
{

	
}