#ifndef V_XML
#define V_XML

/* Foreward Decl */
class TextFile;

/* Includes */
#include "rapidxml/rapidxml.hpp"
#include "UtilAPI.h"

/**
* Definition of the byte to parse xml
*/
#define XmlByte char

/**
* Wrapper class for rapidxml xml_node
*/
class UTIL_API XmlNode
{
private:
	rapidxml::xml_node<XmlByte>* _current; /**<  The xml node this wrapper node is refering to */

public:
	/**
	* Default constructor
	*/
	XmlNode();

	/**
	* Default destructor
	*/
	~XmlNode();

	/**
	* Overloaded constructor to take an xml node
	* @param this_node The node this node will point to
	*/
	XmlNode(rapidxml::xml_node<XmlByte>* this_node);

	/**
	* Copy Constructor
	* @param other The other XmlNode to copy
	*/
	XmlNode(const XmlNode& other);

	/**
	* Returns the value of this node in char * form
	* @return Char* value of this node
	*/
	char* ValueString();

	/**
	* Returns the value of this node in boolean form
	* @return bool Value of this node in boolean form
	*/
	bool ValueBool();

	/**
	* Returns the value of this node in float form
	* @return float value of this node
	*/
	float ValueFloat();

	/**
	* Returns the value of this node in integer form
	* @return integer value of this node
	*/
	int ValueInt();

	/**
	* Gets a string (char*) from a child node 
	* Note that the char* will last as long as the
	* XmlDocument is open
	* @param id The id of the node whos value to get
	*/
	char* GetString(const char* id);

	/**
	* Gets a boolean from a child node 
	* @param id The id of the node whos value to get
	*/
	bool GetBool(const char* id);

	/**
	* Gets a float from a child node
	* @param id The id of the node whos value to get
	*/
	float GetFloat(const char* id);

	/** 
	* Gets a int from a chikd node
	* @param id The id of the node whos value to get
	*/
	int GetInt(const char* id);

	/**
	* Gets a string (char*) from a the current nodes attribute
	* Note that the char* will last as long as the
	* XmlDocument is open
	* @param id The id of the attribute whos value to get
	*/
	char* GetAttributeString(const char* id);

	/**
	* Gets a boolean from the current nodes attribute
	* @param id The id of the attribute whos value to get
	*/
	bool GetAttributeBool(const char* id);

	/**
	* Gets a float from the current nodes attribute
	* @param id The id of the attribute whos value to get
	*/
	float GetAttributeFloat(const char* id);

	/** 
	* Gets a int from the current nodes attribute
	* @param id The id of the attribute whos value to get
	*/
	int GetAttributeInt(const char* id);

	/**
	* Returns the first child node of this node
	* @return XmlNode containing the first child of this node
	* check if IsNull to make sure it was found or not
	*/
	XmlNode FirstChild();

	/**
	* Gets the first child node with the given id
	* @param id The id of the required child node
	* @return The first child (check if IsNull to make sure it was found)
	*/
	XmlNode GetChild(const char* id);

	/**
	* Gets the next sibling node
	* @return The next sibling (check if IsNull to make sure it was found)
	*/
	XmlNode NextSibling();

	/**
	* Gets the next sibling of required id 
	* @param id The id of the next sibling required
	* @return The next sibling (check if IsNull to make sure it was found)
	*/
	XmlNode NextSibling(const char* id);

	/**
	* Returns true if this current node is null 
	* @return Boolean true if _current is pointing to null
	*/
	inline bool IsNull(){ return (_current == NULL); }
};

/**
* Wrapper classes for rapidxml xml_document
*/

class UTIL_API XmlDocument
{
private:
	rapidxml::xml_document<XmlByte>* _doc; /**< The rapidxml xml document */

	TextFile* _tf; /**< The text file containing the xml (must persist through lifetime of document */
public:
	/**
	* Default constructor
	*/
	XmlDocument();

	/**
	* Default destructor
	*/
	~XmlDocument();

	/**
	* Copy Constructor
	* @param other The other XmlDocument who we are copying
	*/
	//XmlDocument(const XmlDocument& other);

	/**
	* Loads the XmlDocument from the given path
	* @param file The path to the file including extension
	* @return Boolean returning true if loaded or false if not.
	*/
	bool Load(const char* file);

	/**
	* Unloads the document (free memory)
	*/
	void Unload();

	/**
	* Gets the root node from the document
	* @return The root XmlNode of _doc
	*/
	XmlNode Root();
};
#endif