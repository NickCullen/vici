#ifndef V_GL_RENDERER
#define V_GL_RENDERER

#include "CoreAPI.h"
#include "glm.h"
#include "PlatformDefinitions.h"
#include "TList.h"

/**
* Constant representing the maximum number of dynamic
* Lights allowed in a scene
*/
const uint32 MAX_LIGHTS = 8;

/*Forward Decl*/
class Camera;
class Light;
class MatrixStack;
class ShaderAsset;
class Transform;

class CORE_API Renderer
{
	friend class Camera;

private:
	//the camera for this renderer
	Camera* _cam;

	//the matrix stack for this renderer
	MatrixStack* _ms;

	//the scene ambience
	glm::vec4 _scene_ambience;
	
	TList<Light*> _lights; /**< The list of lights that may be used in the rendering of the frame */
protected:

public:
	Renderer();
	~Renderer();

	/*if this is override please remember to call base.Init()*/
    void Init(Camera* cam);

	/*Pre scene initialization*/
    void PreSceneRender();

	/*During scene renering */
    void RenderScene();

	/* post scene rendering */
    void PostSceneRender();

	/*override functions*/
    void ClearBuffer(ClearFlags flags, const glm::vec4& col);

	/* sets current matrix on matrix stack to identity */

	/*Inline getters and setters*/
	inline MatrixStack* GetMatrixStack()
	{
		return _ms;
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