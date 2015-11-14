#ifndef V_ASSET
#define V_ASSET

#include "AssetFactory.h"
#include "CoreAPI.h"
#include "PlatformDefinitions.h"
#include "Xml.h"

// Definition for classes that inherit from Asset to put at the
// Top of their definition
#define ASSET_REGISTER_DEF(Asset) 	public: \
			static AssetRegister<Asset> reg; \
			static void Register() \
			{ 						\
				Asset::reg = AssetRegister<Asset>(#Asset); \
			}

// Macro to use to register an asset
#define REG_ASSET(Asset) Asset::Register()

/**
* Base class that all asset types must derive from
* provides pure virtual methods required to load
* and unload assets when required
*/

class CORE_API Asset
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