#ifndef V_IDRAWABLE
#define V_IDRAWABLE

#include "IComponent.h"

/*Forward Decl*/
class OpenGLRenderer;

class IDrawable : public IComponent
{
private:

protected:

public:
	IDrawable();
	virtual ~IDrawable();

	virtual void Init(GameObject* go, rapidxml::xml_node<char>* data);

	virtual void PreRender(OpenGLRenderer* renderer){};
	virtual void OnRender(OpenGLRenderer* renderer){};
	virtual void PostRender(OpenGLRenderer* renderer){};
};

#endif