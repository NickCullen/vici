#ifndef V_MESHRENDERER
#define V_MESHRENDERER

#include "IDrawable.h"

class MeshRenderer : public IDrawable
{
private:
	
protected:

public:
	MeshRenderer();
	~MeshRenderer();

	//init
	virtual void Init(GameObject* go, rapidxml::xml_node<char>* node);

	//required logic functions
	virtual void OnEnable();
	virtual void OnDisable();
	virtual void PreRender(OpenGLRenderer* renderer);
	virtual void OnRender(OpenGLRenderer* renderer);
	virtual void PostRender(OpenGLRenderer* renderer);

	//register functions
	static DerivedRegister<MeshRenderer> reg;

};

#endif