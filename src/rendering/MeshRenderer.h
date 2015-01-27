#ifndef V_MESHRENDERER
#define V_MESHRENDERER

/* Forward decl */
class Material;
class Shader;
class Mesh;

#include "IDrawable.h"

/** 
* Placeholder class for now no comments to follow
*/

class MeshRenderer : public IDrawable
{
private:
	Material* _material; /** The material with the shader that will render this mesh */

	Mesh* _mesh; /**< containing all the mesh data */

	Shader* _shader; /**< The shader to render the mesh */
protected:

public:
	MeshRenderer();
	~MeshRenderer();

	//init
	virtual void Init(rapidxml::xml_node<char>* node);

	//required logic functions
	virtual void OnEnable();
	virtual void OnDisable();

	//implementation of SetupCallbacks
	void OnStart();

	//render functions
	virtual void PreRender(OpenGLRenderer* renderer);
	virtual void OnRender(OpenGLRenderer* renderer);
	virtual void PostRender(OpenGLRenderer* renderer);

	//register functions
	static DerivedRegister<MeshRenderer> reg;

};

#endif