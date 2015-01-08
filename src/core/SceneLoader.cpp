#include "SceneLoader.h"
#include "core.h"
#include <iterator>

/*static defaults*/
Vici* SceneLoader::_v = NULL;
int SceneLoader::_current_level = -1;
std::vector<SceneData> SceneLoader::_scenes = std::vector<SceneData>(0);

SceneLoader::SceneLoader()
{

}

SceneLoader::~SceneLoader()
{

}

void SceneLoader::Init(Vici* v)
{
	if (_v == NULL)
	{
		_v = v;

		char buff[758];

		//set the file path
		strcpy(buff, _v->_cwd);
		strcat(buff, "\\settings\\scenes.xml");

		//instantiate doc and load file
		rapidxml::xml_document<char> doc;
		TextFile tf(buff);

		if (tf.IsLoaded())
		{
			doc.parse<0>(tf);
			rapidxml::xml_node<char>* root = doc.first_node();

			//current scene
			rapidxml::xml_node<char>* cur = root->first_node();
			while (cur != NULL)
			{
				//construct scene data
				SceneData data = SceneData();

				//create its hash id
				data._id = cur->value();

				//set its file and asset dir
				sprintf(data._scene_file, "%s\\scenes\\%s.xml", _v->_cwd, cur->value());
				sprintf(data._scene_assets, "%s\\scenes\\%s_assets.xml", _v->_cwd, cur->value());

				//add to scene data
				_scenes.push_back(data);

				//next
				cur = cur->next_sibling();
			}
			
		}
	}
}

void SceneLoader::UnloadCurrentScene()
{
	for (int i = _v->_objects.size() - 1; i >= 0; i--)
	{
		GameObject* go = _v->_objects[i];
		if (!go->Indestructable())
		{
			_v->_objects.erase(_v->_objects.begin() + i);
			delete(go);
		}

	}
}

void SceneLoader::LoadScene(unsigned int index)
{
	if (index < _scenes.size())
	{
		//load file
		rapidxml::xml_document<char> doc;
		TextFile tf(_scenes[index]._scene_file);
		
		if (tf.IsLoaded())
		{
			doc.parse<0>(tf);
			rapidxml::xml_node<char>* root = doc.first_node();

			//unload current game objects
			UnloadCurrentScene();

			//load game objects
			rapidxml::xml_node<char>* cur = root->first_node("objects")->first_node("gameobject");
			while (cur)
			{
				//instantiate and init GO
				GameObject* go = new GameObject();
				go->Init(NULL, cur);

				//add to scene list
				_v->AddGameObject(go);

				cur = cur->next_sibling();
			}

			_current_level = index;
		}
	}
}
void SceneLoader::LoadScene(char* scene)
{
	//remember to optimize this
	VHash id = scene;
	for (unsigned int i = 0; i < _scenes.size(); i++)
	{
		if (id == _scenes[i]._id)
		{
			LoadScene(i);
			break;
		}
	}
}
