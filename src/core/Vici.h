#ifndef VICI_H
#define VICI_H

//length of cwd
const int BUFF_LEN = 512;

/*Forward decl */
class GameObject;
class VCamera;

#include <vector>

/*Macros for vici access*/
#define _V Vici::Instance()

class Vici
{
	friend class SceneLoader;
	friend class VCamera;
private:
	static Vici* _instance;

	std::vector<GameObject*> _objects;
	std::vector<VCamera*> _cameras;

	bool _started;

	//the cwd
	char _cwd[BUFF_LEN];

	//registers components
	void RegisterComponents();
public:
	Vici();
	~Vici();


	//called once when program begins
	void Init();


	//starts the game
	void Begin();

	/*Update and render funcs*/
	void Update();
	void Render();

	//returns the current working directory (better than Platform_Getcwd as it is cached)
	char* GetCwd();

	/*Testing funcs*/
	void AddGameObject(GameObject* go);

	/* inline getters and seters*/
	static inline Vici* Instance()
	{
		return _instance;
	}
};

#endif