#ifndef V_ASSET_LOADER
#define V_ASSET_LOADER

/* Includes */
#include "SmartPtr.h"
#include "Singleton.h"
#include <map>
#include <string>
#include "Xml.h"

/* Forward Decl */
class Asset;

/* definitions */
typedef std::map<std::string, AssetPointer<Asset> > AssetMap;

/**
* AssetLoader class instantiated in the Vici class and 
* is a singleton. Responsible for maintaining (i.e. loading
* and unloaded) assets between scenes. Can be accessed via the 
* _Assets-> macro defined in Vici.h
*/

class AssetLoader : public Singleton<AssetLoader>
{
	friend class Vici;

private:
	AssetMap _asset_map; /**< All loaded assets */

	/**
	* Unloads all loaded assets (called when application quits)
	*/
	void UnloadAll();

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
	* Gets the asset of given id
	* @param id The id of the asset
	* @return The Asset pointer (if found - else NULL)
	*/
	AssetPointer<Asset> GetAsset(std::string id);

	/**
	* Gets the asset of given id
	* @param id The id of the asset
	* @return The Asset pointer (if found - else NULL)
	*/
	template<typename T>
	AssetPointer<T> GetAsset(std::string id)
	{
		AssetPointer<Asset> asset = GetAsset(id);
		return std::static_pointer_cast<T>(asset);
		//return NULL;
	}

	/**
	* Called by SceneLoader to load the asset from a node
	* @param node The asset node
	*/
	void LoadAsset(XmlNode& node);

};

#endif