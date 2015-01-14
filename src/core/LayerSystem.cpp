#include "LayerSystem.h"
#include "rapidxml/rapidxml.hpp"
#include <string>
#include "TextFile.h"
#include "Platform.h"
//static init
LayerInfo* LayerSystem::_layers = NULL;
unsigned int LayerSystem::_num_of_layers = 0;

void LayerSystem::Init(const char* cwd)
{
	char buff[512];
	sprintf(buff, "%s\\%s.xml", cwd, "settings\\layers");

	//convert slash to correct os filesytem
	strcpy(buff,Platform_Pathify(buff));

	//load xml file
	TextFile tf(buff);

	if (tf.IsLoaded())
	{
		rapidxml::xml_document<char> doc;
		doc.parse<0>(tf);

		rapidxml::xml_node<char>* layers = doc.first_node();

		//as rapidxml does not tell us number of children we need to loop through and count ourselfs :) 
		rapidxml::xml_node<char>* node = layers->first_node();
		while (node)
		{
			_num_of_layers++;
			node = node->next_sibling();
		}

		//if there were layers then create them
		if (_num_of_layers != 0)
		{
			//allocate memory
			_layers = new LayerInfo[_num_of_layers];
			
			//now loop through them again and set the layer info
			rapidxml::xml_node<char>* node = layers->first_node();
			for (int i = 0; node; node = node->next_sibling(), i++)
			{
				_layers[i]._layer = atoi(node->first_attribute("id")->value());
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