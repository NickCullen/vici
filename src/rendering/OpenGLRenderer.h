#ifndef V_GL_RENDERER
#define V_GL_RENDERER

#include "core.h"

/*Forward Decl*/
class VCamera;

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

	void SetUniforms(ShaderAsset* shader);
};

#endif