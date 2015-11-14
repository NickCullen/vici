#ifndef V_GL_RENDERER
#define V_GL_RENDERER

#include "CoreAPI.h"
#include "glm.h"
/**
* Constant representing the maximum number of dynamic
* Lights allowed in a scene
*/

/*Forward Decl*/
class VCamera;
class Light;
class MatrixStack;
class ShaderAsset;

class CORE_API Renderer
{
	friend class VCamera;

private:
	//the camera for this renderer
	VCamera* _cam;

	//the matrix stack for this renderer
	MatrixStack* _ms;

	//the scene ambience
	glm::vec4 _scene_ambience;
	
protected:

public:
	Renderer();
	~Renderer();

	/*if this is override please remember to call base.Init()*/
    void Init(VCamera* cam);

	/*Pre scene initialization*/
    void PreSceneRender();

	/*During scene renering */
    void RenderScene();

	/* post scene rendering */
    void PostSceneRender();

	/*override functions*/
    void ClearBuffer(int flags, const glm::vec4& col);

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

};

#endif