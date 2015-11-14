#ifndef V_CAMERA
#define V_CAMERA


#include "IComponent.h"
#include "CoreAPI.h"
#include "glm.h"

/*Forward decl*/
class Renderer;

/**
* Component used to render a layer in the current scene
* this component and renderering in general is still new to the engine
* so not many detailed comments will be made here 
*/

class CORE_API Camera : public IComponent
{
	COMPONENT_REGISTER_DEF(Camera)

	friend class Renderer;
private:
	Renderer* _renderer; /**< Renderer used to draw the objects this camera will render */

	ClearFlags _clear_flags; /**< OpenGL clear flags this camera will clear */

	glm::vec4 _clear_color; /**< Colour of empty scene */

	TList<GameObject*> _render_list; /**< The objects to render */
	
	glm::mat4x4 _projection_mat;	/**< The projection matrix for this camera */

	glm::mat4x4 _view_mat;	/**< The view matrix for this camera */

	float _speed; /**< Movement speed (Debugging - temp) */
	
public:
	/** 
	* Camera constructor 
	*/
	Camera();

	/**
	* Camera destructor
	*/
	~Camera();

	/** 
	* Adds this camera to the _vici camera list and lets it know what
	* layers it will render
	* @param node pointer to xml node containing this components init data
	*/
	virtual void Init(XmlNode& node);

	/**
	* Called so component can register to logic callback functions
	* and interact with other components& game objects
	*/
	void OnStart();

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

	/**
	* Inline function to access the renderer
	* @return Pointer to the scene renderer
	*/
	inline Renderer* GetRenderer()
	{
		return _renderer;
	}

	void Update(); /**< Debug purposes */
};



#endif