#include "SQScriptAsset.h"
#include "Vici.h"
#include "Platform.h"



SQScriptAsset::SQScriptAsset()
{
	_script_file[0] = '\0';	
}

SQScriptAsset::~SQScriptAsset()
{
	
}

void SQScriptAsset::Load(XmlNode& node)
{
	char* path = node.GetString("path");

	if (path)
	{
		//cat and pathify filepath
		sprintf(_script_file, "%s/%s", _Platform->GetCwd(), path);
		_Platform->Pathify(_script_file);

		//compile script
		_Squirrel->CompileFile(_script_file);
	}
	
}
void SQScriptAsset::Unload()
{

}