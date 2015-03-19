#include "AssetLoader.h"
#include "Asset.h"
#include "AssetTypes.h"
#include "AssetFactory.h"
#include <memory>
#include "Vici.h"
AssetLoader::AssetLoader() : Singleton<AssetLoader>(this)
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
		Asset* asset = iter->second;

		//unload it
		asset->Unload();

		//destroy it
		delete(asset);
	}

	//clear map
	_asset_map.clear();
}

Asset* AssetLoader::GetAsset(std::string id)
{
	AssetMap::iterator it = _asset_map.find(id);
	if (it == _asset_map.end())
		return NULL;

	//incrememnt reference count
	it->second->_reference_count++;

	return it->second;
}

void AssetLoader::ReleaseAsset(Asset* asset)
{
	asset->_reference_count--;

	//if 0 unload asset!
	if (asset->_reference_count <= 0)
	{
		//unload
		asset->Unload();
		
		//find where it is in the map
		AssetMap::iterator it = _asset_map.find(asset->_id);
		if (it == _asset_map.end())
			return;

		//remove from map
		_asset_map.erase(it);

		//unload
		delete(asset);
	}
}

void AssetLoader::LoadAsset(XmlNode& node)
{
	char* type = node.GetAttributeString("type");
	char* id = node.GetAttributeString("id");

	_Platform->LogString("Loading asset (%s) id: %s\n", type, id);
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

		//add to map
		_asset_map.insert(std::make_pair(id, asset));
	}
	
}

void AssetLoader::RegisterAssets()
{
	TextureAsset::reg = AssetRegister<TextureAsset>("TextureAsset");
	MeshAsset::reg = AssetRegister<MeshAsset>("MeshAsset");
	ShaderAsset::reg = AssetRegister<ShaderAsset>("ShaderAsset");
	MaterialAsset::reg = AssetRegister<MaterialAsset>("MaterialAsset");
}

