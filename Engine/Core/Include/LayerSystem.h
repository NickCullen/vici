#ifndef V_LAYERSYSTEM
#define V_LAYERSYSTEM

#include "Singleton.h"
#include "CoreAPI.h"

/* Easy access macro */
#define _Layers Singleton<LayerSystem>::Instance()

/*Forward decl*/
class Camera;

#define MAX_LAYER_NAME 64

/**
* structure containing information about the layer so it can be ordered and 
* rendered correctly
*/

struct CORE_API LayerInfo
{
	int32 _layer;	/**< the id for this layer */
	Camera* _renderer;	/**< the camera that will render this layer */
};

/**
* static classed used to initialize all the layers in use for the current scene 
* can be used for getting a reference to the camera that will render this layer
* status(ongoing)
*/
class CORE_API LayerSystem : public Singleton<LayerSystem>
{
private:
	LayerInfo* _layers;	/**< Array of all the layers for the current scene */
	uint32 _num_of_layers; /**< counter for how many layers are in the scene */
public:

	/** 
	* constructor
	*/
	LayerSystem(); 

	/**
	* destructor
	*/
	~LayerSystem(); 

	/**
	* called at the beginning of each scene to load the current layers
	* @param cwd a string containing the current working directory 
	*/
	void Init(const char* cwd); 

	/**
	* sets the camera that will render the specified layer
	* @param cam Camera pointer to the layer renderer
	* @param layer the unsigned integer id for the layer
	*/
	void SetCameraForLayer(Camera* cam, uint32 layer);

	/**
	* Returns the camera that renders the specified layer (can be NULL)
	* @param layer unsigned integer id of the layer you want to get the camera for
	* @return Camera pointer for the camera that will render the layer (can be NULL)
	*/
	Camera* GetCameraForLayer(uint32 layer);
};


#endif