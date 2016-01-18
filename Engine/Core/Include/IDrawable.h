#ifndef V_IDRAWABLE
#define V_IDRAWABLE

#include "IComponent.h"

/**
* Components that require callbacks to render functions should inherit from IDrawable
* if not then they should inheirt from IComponent. Components inheriting this class
* will still be able to use all the functions as a normal IComponent.
*/

class CORE_API IDrawable : public IComponent
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

	template<class Archive>
	void serialize(Archive& ar)
	{
		_SERIALIZE_PARENT(IComponent, ar);
	}

	/*template<class Archive>
	void save(Archive& ar) const
	{
		_SERIALIZE_PARENT(IComponent, ar);
	}*/

	/**
	* Called before rendering a frame
	* @param renderer the renderer being used to render the scene
	*/
	//virtual void PreRender(Renderer* renderer){};
	/**
	* Called once per frame to render the current frame
	* @param renderer the renderer being used to render the scene
	*/
	//virtual void OnRender(Renderer* renderer){};
	/**
	* Called after the scene has been rendered
	* @param renderer the renderer being used to render the scene
	*/
	//virtual void PostRender(Renderer* renderer){};

	/**
	* Called when this IDrawable is destroyed
	*/
	virtual void OnDestroy();
};

#endif