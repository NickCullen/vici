#include "Xml.h"
#include "TextFile.h"

XmlDocument::XmlDocument()
{
	_doc = NULL;
	_tf = NULL;
}

XmlDocument::~XmlDocument()
{
	if (_doc != NULL) delete(_doc);
	if (_tf != NULL) delete(_tf);
}

//XmlDocument::XmlDocument(const XmlDocument& other)
//{
//	_doc = other._doc;
//}

bool XmlDocument::Load(const char* file)
{
	//load the file
	_tf = new TextFile(file);

	//if it was loaded
	if (_tf->IsLoaded())
	{
		//create doc
		_doc = new rapidxml::xml_document<XmlByte>();

		//pass
		_doc->parse<0>(*_tf);

		//return true
		return true;
	}

	//return false
	return false;
}

void XmlDocument::Unload()
{
	if (_doc != NULL)
	{
		delete(_doc);
		_doc = NULL;
	}
}
XmlNode XmlDocument::Root()
{
	return _doc->first_node(); 
}