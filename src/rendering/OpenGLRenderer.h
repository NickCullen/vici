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

protected:

public:
	OpenGLRenderer();
	~OpenGLRenderer();

	/*if this is override please remember to call base.Init()*/
	virtual void Init(VCamera* cam);

	/*Pre scene initialization*/
	virtual void PreSceneRender();

	/*During scene renering */
	virtual void RenderScene();

	/* post scene rendering */
	virtual void PostSceneRender();

	/*override functions*/
	virtual void ClearBuffer(int flags, glm::vec4* col);

	/*Inline getters and setters*/
	inline MatrixStack* GetMatrixStack()
	{
		return &_ms;
	}

	void SetUniforms(Shader* shader);
};

#endif