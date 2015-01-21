#ifndef V_GL_RENDERER
#define V_GL_RENDERER

#include "core.h"

#ifdef _WIN32
#include "glew.h"
#else
#include <OpenGL/GL.h>
#include <OpenGL/GLU.h>
#endif

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
};

/*definitions*/
#define VICI_COLOR_BUFFER_BIT GL_COLOR_BUFFER_BIT
#define VICI_DEPTH_BUFFER_BIT GL_DEPTH_BUFFER_BIT
#define VICI_ACCUM_BUFFER_BIT GL_ACCUM_BUFFER_BIT
#define VICI_STENCIL_BUFFER_BIT GL_STENCIL_BUFFER_BIT

#endif