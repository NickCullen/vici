// Structure implementations for OpenGL
#ifndef RENDERSTRUCTS
#define RENDERSTRUCTS

/**
 * Clear flags in OpenGL are simply uints
 */
typedef GLbitfield ClearFlags;

/**
 * Texture mode defintions 
 */
typedef uint32 TextureMode;

/**
 * Uniform locations for OpenGL are simply integers so
 * a typedef is all that is needed
 */
 typedef GLint UniformHandle;

 /**
  * Shader program handles in opengl are simply unsigned integers
  */
 typedef GLuint ShaderHandle;

 /**
  * Texture sampler shader handle 
  */
 typedef UniformHandle SamplerHandle;

 /**
  * Texture handle for textures on GPU 
  */
 typedef uint32 TextureHandle;

 /**
  * flags for debugging shaders
  */
 typedef GLenum ShaderDebugFlags;

 /**
  * Buffer handles in opengl are uints 
  */
 typedef GLuint BufferHandle;


 /**
  * Function for getting uniform locations in shaders
  */
#define GetUniformLocationFunc glGetUniformLocation

 /**
  * Function for getting attrib locations in shaders
  */
#define GetAttribLocationFunc glGetAttribLocation
#endif
