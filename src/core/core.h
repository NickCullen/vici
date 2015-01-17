/*definitions*/
#define _CRT_SECURE_NO_WARNINGS
#define NULL 0

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

/*Util*/
#include "TextFile.h"

/*Renderering*/
#include "OpenGLRenderer.h"
#include "MatrixStack.h"

/*Data structures*/
#include "TStack.h"
#include "TList.h"
#include "TListIter.h"