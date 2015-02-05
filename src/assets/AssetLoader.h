#ifndef V_ASSET_LOADER
#define V_ASSET_LOADER

/* Includes */
#include <map>
#include <string>
#include "Xml.h"

/* Forward Decl */
class Asset;

/* definitions */
typedef std::map<std::string, Asset*> AssetMap;

class AssetLoader
{
private:
	AssetMap _asset_map; /**< All loaded assets */

public:
	/**
	* Default constructor 
	*/
	AssetLoader();

	/**
	* Default destructor
	*/
	~AssetLoader();

	/**
	* Called to register all asset types to the AssetFactory 
	*/
	void RegisterAssets();

	/**
	* Gets the asset of given id - will incrememnt
	* assets reference count by one
	* @param id The id of the asset
	* @return The Asset pointer (if found - else NULL)
	*/
	Asset* GetAsset(std::string id);

	/**
	* Deducts 1 for the given asset
	* @param asset The asset who we are releasing a reference to
	*/
	void ReleaseAsset(Asset* asset);

	/**
	* Called by SceneLoader to load the asset from a node
	* @param node The asset node
	*/
	void LoadAsset(XmlNode& node);

};

#endif