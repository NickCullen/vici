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

		//convert slash to correct os filesytem
		strcpy(buff,Platform_Pathify(buff));

		//instantiate doc and load file
		XmlDocument doc;

		if (doc.Load(buff))
		{
			XmlNode root = doc.Root();

			//current scene
			XmlNode cur = root.FirstChild();
			while (!cur.IsNull())
			{
				//construct scene data
				SceneData data = SceneData();

				//create its hash id
				data._id = cur.ValueString();

				//set its file and asset dir
				sprintf(data._scene_file, "%s\\scenes\\%s.xml", _v->_cwd, cur.ValueString());
				sprintf(data._scene_assets, "%s\\scenes\\%s_assets.xml", _v->_cwd, cur.ValueString());

                //make them sensible to current platform file system
                strcpy(data._scene_file, Platform_Pathify(data._scene_file));
                strcpy(data._scene_assets, Platform_Pathify(data._scene_assets));
                
				//add to scene data
				_scenes.push_back(data);

				//next
				cur = cur.NextSibling();
			}
			
		}
	}
}

void SceneLoader::UnloadCurrentScene()
{
	//TODO: needs fixing

	/*for (int i = _v->_objects.size() - 1; i >= 0; i--)
	{
		GameObject* go = _v->_objects[i];
		if (!go->Indestructable())
		{
			_v->_objects.erase(_v->_objects.begin() + i);
			delete(go);
		}

	}*/
}

void SceneLoader::LoadScene(unsigned int index)
{
	if (index < _scenes.size())
	{
		//load file
		XmlDocument doc;

		if (doc.Load(_scenes[index]._scene_file))
		{
			XmlNode root = doc.Root();

			//unload current game objects
			UnloadCurrentScene();

			//load game objects
			XmlNode cur = root.GetChild("objects").GetChild("gameobject");
			while (!cur.IsNull())
			{
				//instantiate and init GO
				GameObject* go = new GameObject();
				go->Init(NULL, cur);

				//add to scene list
				_v->AddGameObject(go);

				cur = cur.NextSibling();
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
