#ifndef V_LAYERSYSTEM
#define V_LAYERSYSTEM

/*Forward decl*/
class VCamera;

#define MAX_LAYER_NAME 64

/**
* structure containing information about the layer so it can be ordered and 
* rendered correctly
*/

struct LayerInfo
{
	int _layer;	/**< the id for this layer */
	VCamera* _renderer;	/**< the camera that will render this layer */
};

/**
* static classed used to initialize all the layers in use for the current scene 
* can be used for getting a reference to the camera that will render this layer
* status(ongoing)
*/
class LayerSystem
{
private:
	static LayerInfo* _layers;	/**< Array of all the layers for the current scene */
	static unsigned int _num_of_layers; /**< counter for how many layers are in the scene */
public:

	/** 
	* Unused constructor
	*/
	LayerSystem(){}; 

	/**
	* Unused destructor
	*/
	~LayerSystem(){}; 

	/**
	* called at the beginning of each scene to load the current layers
	* @param cwd a string containing the current working directory 
	*/
	static void Init(const char* cwd); 

	/**
	* sets the camera that will render the specified layer
	* @param cam VCamera pointer to the layer renderer
	* @param layer the unsigned integer id for the layer
	*/
	static void SetCameraForLayer(VCamera* cam, unsigned int layer);

	/**
	* Returns the camera that renders the specified layer (can be NULL)
	* @param layer unsigned integer id of the layer you want to get the camera for
	* @return VCamera pointer for the camera that will render the layer (can be NULL)
	*/
	static VCamera* GetCameraForLayer(unsigned int layer);
};


#endif