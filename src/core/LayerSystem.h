#ifndef V_LAYERSYSTEM
#define V_LAYERSYSTEM

/*Forward decl*/
class VCamera;

#define MAX_LAYER_NAME 64

struct LayerInfo
{
	//the layer number
	int _layer;
	//the camera to render this layer
	VCamera* _renderer;

};

class LayerSystem
{
private:
	//array of layer infos
	static LayerInfo* _layers;
	static unsigned int _num_of_layers;
public:
	//irrelevant ctor and dtor
	LayerSystem(){};
	~LayerSystem(){};

	//init from xml
	static void Init(const char* cwd);

	//sets the camera
	static void SetCameraForLayer(VCamera* cam, unsigned int layer);

	//get the camera for a specfic layer
	static VCamera* GetCameraForLayer(unsigned int layer);
};


#endif