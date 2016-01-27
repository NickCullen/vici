#ifndef _V_SMART_PTR
#define _V_SMART_PTR

//use std library for pointers - let sbe sensible....

#include <memory>

//typedefs
#define SharedReference std::shared_ptr

//Asset pointers
#define AssetPointerDef SharedReference

// Component Pointers
#define ComponentPtrDef SharedReference
#define ComponentPtr ComponentPtrDef<IComponent>

// classes that derive from Object
#define ObjectPtrDef SharedReference
#define ObjectPtr ObjectPtrDef<Object>
#define SubObjectPtr ObjectPtrDef

// Game Object Pointer
#define GameObjectPtr SubObjectPtr<GameObject>

#endif