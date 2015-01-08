#ifndef V_CAMERA
#define V_CAMERA

#include "IDrawable.h"

/*Forward decl*/
class OpenGLRenderer;

/*Camera clear flags

	GL_COLOR_BUFFER_BIT
		Indicates the buffers currently enabled for color
		writing.
	GL_DEPTH_BUFFER_BIT
		Indicates the depth buffer.
	GL_ACCUM_BUFFER_BIT
		Indicates the accumulation buffer.
	GL_STENCIL_BUFFER_BIT
		Indicates the stencil buffer.

*/
class VCamera : public IDrawable
{
private:
	//the renderer
	OpenGLRenderer* _renderer;

	//clear flags
	unsigned int _clear_flags;

	//clear color
	glm::vec4 _clear_color;

	//game objects to render
	std::vector<GameObject*> _render_list;
	
	//the projection matrix
	glm::mat4x4 _projection_mat;

public:
	VCamera();
	~VCamera();

	//override some stuff
	virtual void Init(GameObject* go, rapidxml::xml_node<char>* node);

	//set up before rendering
	void PrepareScene();

	//renderings
	void Render();

	//adds a game object to the render list
	void AddGameObject(GameObject* go);
	void RemoveGameObject(GameObject* go);

	//register function
	static DerivedRegister<VCamera> reg;

};



#endif