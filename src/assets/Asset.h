#ifndef V_ASSET
#define V_ASSET

#include "AssetFactory.h"
#include "PlatformDefinitions.h"
#include "Xml.h"

class Asset
{
	friend class AssetLoader;
private:
	int16 _reference_count;	/**< Number of items that reference this asset */

protected:
	std::string _id; /**< The id of the asset */

public:
	Asset();

	~Asset();

	virtual void Load(XmlNode& node) = 0;
	virtual void Unload() = 0;

};








#endif