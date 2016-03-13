#include "ObjImporter.h"
#include "FilePath.h"
#include <fstream>
#include <string>
#include "VString.h"

OBJImporter::OBJImporter()
{

}

OBJImporter::~OBJImporter()
{

}

bool OBJImporter::Import(const VFilePath& file)
{
	std::ifstream infile((const char*)file);
	std::string line;

	std::string currentObject = "";
	while (std::getline(infile, line))
	{
		// Comment
		if (line.front() == '#')
			continue;

		// Object name
		else if (line.front() == 'o')
			currentObject = line.substr(2, line.length() - 2);

		// Tex coord
		else if (line.find("vt") == line.front())
		{
			printf("Texture coord\n");
		}

		// Vertex Normal
		else if (line.find("vn") == line.front())
		{
			printf("Normal\n");
		}

		// Vertex Coord
		else if (line.front() == 'v')
		{
			printf("Vertex\n");
		}

		// Material file
		else if (line.find("mtllib") != std::string::npos)
			ParseMaterialFile(file.GetDirectory(), line.c_str());
	}

	return true;
}

void OBJImporter::ParseMaterialFile(const VString& directory, const VString& mtline)
{

	
}