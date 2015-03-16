#ifndef V_ASSET_FACTORY
#define V_ASSET_FACTORY

/*Forward Decl*/
class Asset;

/*for mapping of instances and creation functions*/
#include<map>
#include<string>

/*definition for the creation function of a asset */
template<typename T> Asset* CreateAssetInstance() { return new T; }

/*the typedef for the hash table of mappings*/
typedef std::map<std::string, Asset*(*)()> AssetMapType;

/**
* Static class holding a Hashtable of registered asset creation functions
* Used to instantiate assets type via strings.
* Status(Complete)
*/

class AssetFactory
{
private:
	static AssetMapType* _types; /**< static hash table containing creation function for registered assets */

protected:

	/**
	* Getter function for returning the hashtable for registered assets
	* @return Hashtable containing registered assets
	*/
	inline static AssetMapType* GetTypes()
	{
		if (_types == NULL) _types = new AssetMapType();
		return _types;
	}

	/**
	* Internal function used to find a registered class' creation function on the hash table
	* @param id string containing id of required asset
	* @return The found asset (NULL if not found)
	*/
	static Asset* FindType(std::string id);

public:
	/**
	* Not Used
	*/
	AssetFactory();
	/**
	* Not Used
	*/
	~AssetFactory();

	/**
	* Function that instantiates a asset given the id
	* @param id string containing id of required asset
	* @return The created asset pointer (NULL if not created)
	*/
	static Asset* CreateAsset(std::string id);

	/**
	* Called to cleanup the types when program closes
	*/
	static void CleanUp();
};

/**
* The AssetRegister class is instantiated by every asset to register their creation function
* so they can be instantiated later on (e.g. asset loading) via strings
* Status(Complete)
*/

template<typename T>
class AssetRegister : AssetFactory
{
public:

	/**
	* The constructor used by the asset to register its creation function
	* @param s The string id of the asset
	*/
	AssetRegister(std::string s)
	{
		GetTypes()->insert(std::make_pair(s, &CreateAssetInstance<T>));
	}
};

#endif

