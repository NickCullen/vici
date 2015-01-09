#include "ComponentFactory.h"

/*Static init*/
MapType* ComponentFactory::_types = NULL;

ComponentFactory::ComponentFactory()
{

}
ComponentFactory::~ComponentFactory()
{

}

IComponent* ComponentFactory::FindType(std::string id)
{
	MapType::iterator it = GetTypes()->find(id);
	if (it == GetTypes()->end())
		return 0;
	return it->second();
}

IComponent* ComponentFactory::CreateComponent(std::string id)
{
	return FindType(id);
}