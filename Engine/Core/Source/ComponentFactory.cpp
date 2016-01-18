#include "ComponentFactory.h"

/*Static init*/
MapType* ComponentFactory::Types = NULL;

ComponentFactory::ComponentFactory()
{

}
ComponentFactory::~ComponentFactory()
{

}

ComponentPtr ComponentFactory::FindType(Hash id)
{
	MapType::iterator it = GetTypes()->find(id);
	if (it == GetTypes()->end())
		return 0;
	return it->second();
}

ComponentPtr ComponentFactory::CreateComponent(Hash id)
{
	return FindType(id);
}

void ComponentFactory::CleanUp()
{
	if(Types != NULL)
	{
		Types->clear();
		delete(Types);
		Types = NULL;
	}
}