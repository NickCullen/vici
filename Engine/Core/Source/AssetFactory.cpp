#include "AssetFactory.h"

/*Static init*/
AssetMapType* AssetFactory::Types = NULL;

AssetFactory::AssetFactory()
{

}
AssetFactory::~AssetFactory()
{

}

Asset* AssetFactory::FindType(Hash id)
{
	AssetMapType::iterator it = GetTypes()->find(id);
	if (it == GetTypes()->end())
		return 0;
	return it->second();
}

Asset* AssetFactory::CreateAsset(Hash id)
{
	return FindType(id);
}

void AssetFactory::CleanUp()
{
	if (Types != NULL)
	{
		Types->clear();
		delete(Types);
		Types = NULL;
	}
}