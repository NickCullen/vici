#ifndef V_GL_RENDERER
#define V_GL_RENDERER

#include "core.h"


#ifdef _WIN32
#include "glew.h"
#else
#include <gl/GL.h>
#include <gl/GLU.h>
#endif

class VCamera;

class OpenGLRenderer
{
private:

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
};

//defines
#define VICI_COLOR_BUFFER_BIT GL_COLOR_BUFFER_BIT
#define VICI_DEPTH_BUFFER_BIT GL_DEPTH_BUFFER_BIT
#define VICI_ACCUM_BUFFER_BIT GL_ACCUM_BUFFER_BIT
#define VICI_STENCIL_BUFFER_BIT GL_STENCIL_BUFFER_BIT

#endif