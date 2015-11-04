#ifndef V_ASSET
#define V_ASSET

#include "AssetFactory.h"
#include "PlatformDefinitions.h"
#include "Xml.h"

/**
* Base class that all asset types must derive from
* provides pure virtual methods required to load
* and unload assets when required
*/

class Asset
{
	friend class AssetLoader;
private:

protected:
	std::string _id; /**< The id of the asset - Used to retrieve asset from the asset database*/

public:
	/**
	* Default constructor
	*/
	Asset();

	/**
	* Default destructor
	*/
	virtual ~Asset();

	/**
	* Pure virtual method called when asset is
	* required to load its contents. Note that
	* all assets must be able to reload themselves
	* after Unloaded when required (safety for some
	* mobile devices)
	* @param node The XmlNode containing the data for this asset
	*/
	virtual void Load(XmlNode& node) = 0;

	/**
	* Pure virtual method called when the asset is to be unloaded
	*/
	virtual void Unload() = 0;

};








#endif