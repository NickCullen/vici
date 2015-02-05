#include "MaterialAsset.h"
#include "Vici.h"
#include "Platform.h"

MaterialAsset::MaterialAsset() : Asset()
{
	_ns = _d = 0.0f;
	_illum = 1;
}

MaterialAsset::~MaterialAsset()
{

}

void MaterialAsset::Load(XmlNode& node)
{
	char buff[BUFFER_SIZE];
	
	//material path
	char* path = node.GetString("path");
	sprintf(buff, "%s/%s", _vici->GetCwd(), path);
	strcpy(buff, Platform_Pathify(buff));

	//load the material file
	XmlDocument doc;
	if (doc.Load(buff))
	{
		XmlNode root = doc.Root();

		//get default properties
		_ns = root.GetFloat("ns");
		sscanf(root.GetString("ka"), "%f %f %f %f", &_ka[0], &_ka[1], &_ka[2], &_ka[3]);
		sscanf(root.GetString("kd"), "%f %f %f %f", &_kd[0], &_kd[1], &_kd[2], &_kd[3]);
		sscanf(root.GetString("ks"), "%f %f %f %f", &_ks[0], &_ks[1], &_ks[2], &_ks[3]);

		_d = root.GetFloat("d");
		_illum = root.GetInt("illum");
	}
}

void MaterialAsset::Unload()
{

}


