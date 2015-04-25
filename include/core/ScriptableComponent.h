#ifndef V_SCRIPTABLE_COMPONENT
#define V_SCRIPTABLE_COMPONENT

#include "IDrawable.h"

class ScriptableComponent : public IDrawable
{
private:

protected:

public:
	ScriptableComponent();

	~ScriptableComponent();

	virtual void MyFunc();

	static ComponentRegister<ScriptableComponent> reg;
};
#endif