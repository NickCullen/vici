/*definitions*/
#define _CRT_SECURE_NO_WARNINGS
#define GLM_FORCE_PURE

/*External libs*/
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "rapidxml/rapidxml.hpp"

/*Platform Includes*/
#include "Platform.h"
#include "Display.h"

/*Engine core*/
#include "Vici.h"
#include "OpenGLRenderer.h"
#include "GameObject.h"
#include "VHash.h"
#include "SceneLoader.h"
#include "Object.h"
#include "ComponentFactory.h"
#include "LayerSystem.h"
#include "Transform.h"

/*Util*/
#include "TextFile.h"
