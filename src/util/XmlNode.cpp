#include "Xml.h"
#include <string>

XmlNode::XmlNode()
{
	_current = NULL;
}

XmlNode::~XmlNode()
{

}

XmlNode::XmlNode(rapidxml::xml_node<XmlByte>* this_node)
{
	_current = this_node;
}

XmlNode::XmlNode(const XmlNode& other)
{
	_current = other._current;
}

char* XmlNode::GetString(char* id)
{
	char* ret = NULL;
	if (_current != NULL)
	{
		rapidxml::xml_node<XmlByte>* child = _current->first_node(id);
		if (child != NULL)
		{
			ret = child->value();
		}
	}
	return ret;
}

bool XmlNode::GetBool(char* id)
{
	bool ret = false;
	if (_current != NULL)
	{
		rapidxml::xml_node<XmlByte>* child = _current->first_node(id);
		if (child != NULL)
		{
			ret = (strcmp(child->value(),"true")==0);
		}
	}
	return ret;
}

float XmlNode::GetFloat(char* id)
{
	float ret = 0.0f;
	if (_current != NULL)
	{
		rapidxml::xml_node<XmlByte>* child = _current->first_node(id);
		if (child != NULL)
		{
			sscanf(child->value(), "%f", &ret);
		}
	}
	return ret;
}

int XmlNode::GetInt(char* id)
{
	int ret = 0;
	if (_current != NULL)
	{
		rapidxml::xml_node<XmlByte>* child = _current->first_node(id);
		if (child != NULL)
		{
			sscanf(child->value(), "%d", &ret);
		}
	}
	return ret;
}

char* XmlNode::GetAttributeString(char* id)
{
	char* ret = NULL;
	if (_current != NULL)
	{
		rapidxml::xml_attribute<XmlByte>* child = _current->first_attribute(id);
		if (child != NULL)
		{
			ret = child->value();
		}
	}
	return ret;
}

bool XmlNode::GetAttributeBool(char* id)
{
	bool ret = false;
	if (_current != NULL)
	{
		rapidxml::xml_attribute<XmlByte>* child = _current->first_attribute(id);
		if (child != NULL)
		{
			ret = (strcmp(child->value(), "true") == 0);
		}
	}
	return ret;
}

float XmlNode::GetAttributeFloat(char* id)
{
	float ret = 0.0f;
	if (_current != NULL)
	{
		rapidxml::xml_attribute<XmlByte>* child = _current->first_attribute(id);
		if (child != NULL)
		{
			sscanf(child->value(), "%f", &ret);
		}
	}
	return ret;
}

int XmlNode::GetAttributeInt(char* id)
{
	int ret = 0;
	if (_current != NULL)
	{
		rapidxml::xml_attribute<XmlByte>* child = _current->first_attribute(id);
		if (child != NULL)
		{
			sscanf(child->value(), "%d", &ret);
		}
	}
	return ret;
}

XmlNode XmlNode::FirstChild()
{
	return IsNull() ? XmlNode() : _current->first_node();
}

XmlNode XmlNode::GetChild(char* id)
{
	return IsNull() ? XmlNode() : _current->first_node(id);
}

XmlNode XmlNode::NextSibling()
{
	return IsNull() ? XmlNode() : _current->next_sibling();
}

XmlNode XmlNode::NextSibling(char* id)
{
	return IsNull() ? XmlNode() : _current->next_sibling(id);
}

char* XmlNode::ValueString()
{
	char* ret = NULL;
	if (_current != NULL)
	{
		ret = _current->value();
	}
	return ret;
}

bool XmlNode::ValueBool()
{
	bool ret = false;
	if (_current != NULL)
	{
		ret = (strcmp(_current->value(), "true") == 0);
	}
	return ret;
}

float XmlNode::ValueFloat()
{
	float ret = 0.0f;
	if (_current != NULL)
	{
		sscanf(_current->value(), "%f", &ret);
	}
	return ret;
}

int XmlNode::ValueInt()
{
	int ret = 0;
	if (_current != NULL)
	{
		sscanf(_current->value(), "%d", &ret);
	}
	return ret;
}