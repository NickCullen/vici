/*definitions*/
#ifndef NULL
#define NULL 0
#endif

/*External libs*/
#include "glm.h"
#include "rapidxml/rapidxml.hpp"

/*Platform Includes*/
#include "Platform.h"
#include "Display.h"

/*Engine core*/
#include "Vici.h"
#include "GameObject.h"
#include "VHash.h"
#include "SceneLoader.h"
#include "Object.h"
#include "ComponentFactory.h"
#include "LayerSystem.h"
#include "Transform.h"
#include "Delegate.h"
#include "GameObjectTree.h"
#include "ComponentTree.h"

/*Util*/
#include "TextFile.h"

/*Renderering*/
#include "OpenGLRenderer.h"
#include "MatrixStack.h"
#include "Shader.h"

/*Data structures*/
#include "tds.h"