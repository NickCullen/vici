#ifndef _V_SMART_PTR
#define _V_SMART_PTR

//use std library for pointers - let sbe sensible....

#include <memory>

//typedefs
#define SharedReference std::shared_ptr

//engine pointers
#define AssetPointer SharedReference

#define ComponentPtrDef SharedReference
#define ComponentPtr ComponentPtrDef<IComponent>



#endif