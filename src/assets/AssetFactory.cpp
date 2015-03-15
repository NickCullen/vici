#include "AssetFactory.h"

/*Static init*/
AssetMapType* AssetFactory::_types = NULL;

AssetFactory::AssetFactory()
{

}
AssetFactory::~AssetFactory()
{

}

Asset* AssetFactory::FindType(std::string id)
{
	AssetMapType::iterator it = GetTypes()->find(id);
	if (it == GetTypes()->end())
		return 0;
	return it->second();
}

Asset* AssetFactory::CreateAsset(std::string id)
{
	return FindType(id);
}

void AssetFactory::CleanUp()
{
	if (_types != NULL)
	{
		_types->clear();
		delete(_types);
		_types = NULL;
	}
}