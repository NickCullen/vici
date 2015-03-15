#ifndef V_MESHRENDERER
#define V_MESHRENDERER

/* Forward decl */
class Material;

#include "IDrawable.h"

/** 
* Placeholder class for now no comments to follow
*/

class MeshRenderer : public IDrawable
{
private:
	Material* _material; /** The material with the shader that will render this mesh */

	MeshAsset* _mesh; /**< containing all the mesh data */

	ShaderAsset* _shader; /**< The shader to render the mesh */

	int32 _indices; /**< id of the index array to use in the mesh */

	bool _recieve_lighting; /**< Flag specifying if this mesh will recieve lighting or not (default = true) */
protected:

public:
	MeshRenderer();
	~MeshRenderer();

	//init
	virtual void Init(XmlNode& node);

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
	static ComponentRegister<MeshRenderer> reg;


	//for testing
	void Update();
};

#endif