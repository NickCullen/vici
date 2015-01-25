#ifndef V_IDRAWABLE
#define V_IDRAWABLE

#include "IComponent.h"

/*Forward Decl*/
class OpenGLRenderer;

/**
* Components that require callbacks to render functions should inherit from IDrawable
* if not then they should inheirt from IComponent. Components inheriting this class
* will still be able to use all the functions as a normal IComponent.
*/

class IDrawable : public IComponent
{
private:

protected:

public:

	/**
	* IDrawable constructor 
	*/
	IDrawable();

	/**
	* IDrawable destructor
	*/
	virtual ~IDrawable();

	/**
	* Called when a component is created via xml. No references should be made to other
	* components in this function as there is no guarantee that they may be instantiated yet.
	* Idrawable will call the parent (IComponent) Init function. note that components
	* inheriting from this class MUST call IDrawable::Init(data) 
	* @param data the xml node containing the required loading information
	*/
	virtual void Init(rapidxml::xml_node<char>* data);

	/**
	* Called before rendering a frame
	* @param renderer the renderer being used to render the scene
	*/
	virtual void PreRender(OpenGLRenderer* renderer){};
	/**
	* Called once per frame to render the current frame
	* @param renderer the renderer being used to render the scene
	*/
	virtual void OnRender(OpenGLRenderer* renderer){};
	/**
	* Called after the scene has been rendered
	* @param renderer the renderer being used to render the scene
	*/
	virtual void PostRender(OpenGLRenderer* renderer){};

	/**
	* Called when this IDrawable is destroyed
	*/
	virtual void OnDestroy();
};

#endif