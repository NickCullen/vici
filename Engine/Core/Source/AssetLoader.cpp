#include "AssetLoader.h"
#include "Asset.h"
#include "AssetFactory.h"
#include <memory>

AssetLoader::AssetLoader() : Singleton<AssetLoader>()
{
	
}

AssetLoader::~AssetLoader()
{
	UnloadAll();
}

void AssetLoader::UnloadAll()
{
	AssetMap::iterator iter;

	for (iter = _asset_map.begin(); iter != _asset_map.end(); ++iter) 
	{
		//get asset
		Asset* asset = iter->second.get();

		//unload it
		asset->Unload();
	}

	//clear map - will destroy pointers for us thanks to smart pointers
	_asset_map.clear();
}

AssetPointer<Asset> AssetLoader::GetAsset(VHash id)
{
	AssetMap::iterator it = _asset_map.find(id);
	if (it == _asset_map.end())
		return AssetPointer<Asset>(NULL);

	return it->second;
}

void AssetLoader::LoadAsset(XmlNode& node)
{
	char* type = node.GetAttributeString("type");
	char* id = node.GetAttributeString("id");

	//dont load if any params are NULL
	if (id == NULL || type == NULL)
	{
		return;
	}

	//and dont load if already on the list
	if (_asset_map.find(id) == _asset_map.end())
	{
		//create asset
		Asset* asset = AssetFactory::CreateAsset(type);

		//set values
		asset->_id = id;

		//load it up
		asset->Load(node);

		//create ptr 
		AssetPointer<Asset> ptr = AssetPointer<Asset>(asset);

		//add to map
		_asset_map.insert(std::make_pair(id, ptr));
	}
	
}


