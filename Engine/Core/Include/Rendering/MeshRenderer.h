#ifndef V_MESHRENDERER
#define V_MESHRENDERER

/* Forward decl */
class Material;

#include "IDrawable.h"
#include "CoreAPI.h"
#include "MeshAsset.h"
#include "SmartPtr.h"

/** 
* Renders a mesh using the material
* that is attached to the same GameObject.
*/

class CORE_API MeshRenderer : public IDrawable
{
private:
	Material* _material; /** The material with the shader that will render this mesh */

	AssetPointer<MeshAsset> _mesh; /**< containing all the mesh data */

	int32 _indices; /**< id of the index array to use in the mesh */

	bool _recieve_lighting; /**< Flag specifying if this mesh will recieve lighting or not (default = true) */
protected:

public:
	/**
	* Default constructor
	*/
	MeshRenderer();

	/** 
	* Default destructor
	*/
	~MeshRenderer();

	/**
	* Called to load MeshRenderer from xml node
	* @param node The XmlNode containing the data for this MeshRenderer
	*/
	virtual void Init(XmlNode& node);

	/**
	* Called when object becomes enabled to add
	* itself to the camera render list
	*/
	virtual void OnEnable();

	/**
	* Called when object becomes disabled to 
	* remove itself from the cameras render list
	*/
	virtual void OnDisable();

	/**
	* Called to register for callbacks
	*/
	void OnStart();

	/**
	* Called in the main render cycle to render 
	* the mesh with the desired material
	* @param renderer The OpenGLRenderer used to render this mesh
	*/
	virtual void OnRender(Renderer* renderer);

	static ComponentRegister<MeshRenderer> reg; /**< Static member var used to register this component with the ComponentFactory */
};

#endif