#include "LayerSystem.h"
#include "Xml.h"
#include <string>
#include "TextFile.h"
#include "Vici.h"

LayerSystem::LayerSystem() : Singleton<LayerSystem>()
{
	_layers = NULL;
	_num_of_layers = 0;
}

LayerSystem::~LayerSystem()
{
	delete[] _layers;
}

void LayerSystem::Init(const char* cwd)
{
	char buff[512];
	sprintf(buff, "%s\\%s.xml", cwd, "settings\\layers");

	//convert slash to correct os filesytem
	strcpy(buff,_Platform->Pathify(buff));

	XmlDocument doc;

	if (doc.Load(buff))
	{
		XmlNode layers = doc.Root();

		//as rapidxml does not tell us number of children we need to loop through and count ourselfs :) 
		XmlNode node = layers.FirstChild();
		while (!node.IsNull())
		{
			_num_of_layers++;
			node = node.NextSibling();
		}

		//if there were layers then create them
		if (_num_of_layers != 0)
		{
			//allocate memory
			_layers = new LayerInfo[_num_of_layers];
			
			//now loop through them again and set the layer info
			XmlNode node = layers.FirstChild();
			for (int i = 0; !node.IsNull(); node = node.NextSibling(), i++)
			{
				_layers[i]._layer = node.GetAttributeInt("id");
				_layers[i]._renderer = NULL; 
			}

		}
	}
}

//sets the camera
void LayerSystem::SetCameraForLayer(VCamera* cam, unsigned int layer)
{
	if (_layers != NULL && layer < _num_of_layers)
	{
		_layers[layer]._renderer = cam;
	}
	else
	{
		printf("could not set camera for layer\n");
	}
}

VCamera* LayerSystem::GetCameraForLayer(unsigned int layer)
{
	if (_layers != NULL && layer < _num_of_layers)
	{
		return _layers[layer]._renderer;
	}
	else
	{
		printf("could not get camera for layer\n");
		return NULL;
	}
}