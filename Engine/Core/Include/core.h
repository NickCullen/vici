/*definitions*/
#ifndef NULL
#define NULL 0
#endif

/*External libs*/
#include "glm.h"

/*Platform Includes*/
#include "Platform.h"
#include "Display.h"
#include "Input.h"

/*Debug + Logging methods*/
#include "Logger.h"

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
#include "VTime.h"

/*Util*/
#include "TextFile.h"
#include "Xml.h"
#include "SmartPtr.h"

/*Renderering*/
#include "OpenGLRenderer.h"
#include "MatrixStack.h"
#include "ShaderAsset.h"
#include "TextureAsset.h"
#include "MeshAsset.h"
#include "MaterialAsset.h"

/*Data structures*/
#include "tds.h"

/*Assets*/
#include "AssetLoader.h"
#include "Asset.h"