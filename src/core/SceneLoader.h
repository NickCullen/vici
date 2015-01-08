#ifndef V_SCENELOADER
#define V_SCENELOADER

#include "VHash.h"
#include <vector>

/*Forward Decl*/
class Vici;

//structure holding scene data
struct SceneData
{
	VHash _id;
	char _scene_file[512];
	char _scene_assets[512];
};

class SceneLoader
{
friend class Vici;
private:
	static Vici* _v;
	static int _current_level;
	static std::vector<SceneData> _scenes;

	//only Vici calls this
	static void Init(Vici* v);

	//deletes all objects in the current scene (if not indestructable of course)
	static void UnloadCurrentScene();
public:
	SceneLoader();
	virtual ~SceneLoader();

	//loading
	static void LoadScene(unsigned int index);
	static void LoadScene(char* scene);
};

#endif