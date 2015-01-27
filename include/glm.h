/*Compiler definitions for glm*/
#define GLM_FORCE_PURE

/* Force inline wont work on mac */
#ifndef VICI_MAC
#define GLM_FORCE_INLINE 
#endif

/*glm includes*/
#include "glm/glm.hpp"
#include "glm/ext.hpp"

/* Include GLM extensions */
#include <glm/gtc/matrix_transform.hpp>
