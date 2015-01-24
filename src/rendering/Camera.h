#ifndef V_CAMERA
#define V_CAMERA

#include "IComponent.h"

/*Forward decl*/
class OpenGLRenderer;

/**
* Component used to render a layer in the current scene
* this component and renderering in general is still new to the engine
* so not many detailed comments will be made here 
* status (incomplete - new )
*/

class VCamera : public IComponent
{
private:
	//the renderer
	OpenGLRenderer* _renderer;

	//clear flags
	unsigned int _clear_flags;

	//clear color
	glm::vec4 _clear_color;

	//game objects to render
	TList<GameObject*> _render_list;
	
	//the projection matrix
	glm::mat4x4 _projection_mat;

	//the view matrix
	glm::mat4x4 _view_mat;

public:
	/** 
	* VCamera constructor 
	*/
	VCamera();

	/**
	* VCamera destructor
	*/
	~VCamera();

	/** 
	* Adds this camera to the _vici camera list and lets it know what
	* layers it will render
	* @param go pointer to game object this component is attached to
	* @param node pointer to xml node containing this components init data
	*/
	virtual void Init(GameObject* go, rapidxml::xml_node<char>* node);

	/** 
	* Called by _vici to prepare scene (i.e set clear flags etc.) 
	* just before firing off render callbacks 
	*/
	void PrepareScene();

	/** 
	* Called to render the componets that require drawing
	* this will be called once per frame 
	*/
	void Render();

	/**
	* Adds a game object to the render list (likely to change)
	* @param go game object pointer to add to render list 
	*/
	void AddGameObject(GameObject* go);

	/** 
	* Removes this game object from render list (likely to change)
	* @param go pointer to game object to remove
	*/
	void RemoveGameObject(GameObject* go);

	/**
	* Called when the Component is destroyed
	*/
	void OnDestroy();

	static DerivedRegister<VCamera> reg; /**< Static registration member var used to register this component with the ComponentFactory */

	void Update();
};



#endif