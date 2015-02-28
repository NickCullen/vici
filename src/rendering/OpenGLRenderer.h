#ifndef V_GL_RENDERER
#define V_GL_RENDERER

#include "core.h"

/**
* Constant representing the maximum number of dynamic
* Lights allowed in a scene
*/
const int32 MAX_LIGHTS = 8;

/*Forward Decl*/
class VCamera;
class Light;

class OpenGLRenderer
{
	friend class VCamera;

private:
	//the camera for this renderer
	VCamera* _cam;

	//the matrix stack for this renderer
	MatrixStack _ms;

	//the scene ambience
	glm::vec4 _scene_ambience;

	TList<Light*> _lights; /**< The list of lights that may be used in the rendering of the frame */

protected:

public:
	OpenGLRenderer();
	~OpenGLRenderer();

	/*if this is override please remember to call base.Init()*/
    void Init(VCamera* cam);

	/*Pre scene initialization*/
    void PreSceneRender();

	/*During scene renering */
    void RenderScene();

	/* post scene rendering */
    void PostSceneRender();

	/*override functions*/
    void ClearBuffer(int flags, glm::vec4* col);

	/*Inline getters and setters*/
	inline MatrixStack* GetMatrixStack()
	{
		return &_ms;
	}

	/**
	* sets the default uniforms (note that this doesnt set
	* the lighting uniforms. If this was required see 
	* "SetLightUniforms")
	* @param shader The shader to set uniforms
	*/
	void SetUniforms(ShaderAsset* shader);

	/**
	* sets the light unforms uniforms to the shader
	* @param shader The shader to set uniforms
	* @param transform The transform of the object so we can see if the light will actually effect it or not
	*/
	void SetLightUniforms(ShaderAsset* shader, Transform* transform);

	/**
	* Adds a light to be used in the rendering process
	* @param light Pointer to the light 
	*/
	void AddLight(Light* light);

	/**
	* Removes a light from the light list
	* @param light The light to be removed
	*/
	void RemoveLight(Light* light);
};

#endif