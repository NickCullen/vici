#ifndef V_DELEGATE
#define V_DELEGATE

/** Includes */
#include "CoreAPI.h"

/** Definition for the delegate macro which requires the class type, the method pointer and a pointer to the object */
#define DELEGATE(Type, Method, This) Delegate::NoArgs<Type, &Type::Method>(This)

/** 
* A class which contains a pointer to the class and its required method to call
* it works in the same way as delegates in c# - so far no arguments can be passed in
* for a reference of the code and how it works can be found here : http://www.codeproject.com/Articles/11015/The-Impossibly-Fast-C-Delegates 
*/

class CORE_API Delegate
{
private:
	/** The type def of the stub function which will call the delegate when required */
	typedef void(*stub_type)(void* object_ptr);

	void* ObjectReference;	/**< Void pointer to the object (we need this for referencing its method later) */

	stub_type StubPtr; /**< Reference to the method stub which holds the actual method to call */

	/** 
	* This will be stored in _stub_ptr as the stub method which will hold
	* and eventually call the required method when needed
	* @param object_ptr a pointer to the object who requires delegation
	*/
	template <class T, void (T::*TMethod)(void)>
	static void method_stub(void* object_ptr)
	{
		T* p = static_cast<T*>(object_ptr);
		return (p->*TMethod)(); // #2
	}

public:

	/**
	* Default ctor which initializes pointers to NULL 
	*/
	Delegate();

	/**
	* Default destructor
	*/
	~Delegate();

	/**
	* The method to call to create a delegate (or use the DELEGATE macro above)
	* Requires the object to pass in its Type and method as template parameters
	* and pass a pointer to itself as a pointer and example call would be:
	* Delegate d = Delegate::NoArgs<MyClass, &MyClass::FunctionToCall>(this); 
	* or Delegate d = DELEGATE(MyClass, FunctionToCall, this);
	* @param obj_ptr a pointer to the object who requires delegation
	* @return Returns the created delegate object
	*/
	template <class T, void (T::*TMethod)(void)>
	static Delegate NoArgs(T* object_ptr)
	{
		Delegate d;
		d.ObjectReference = object_ptr;
		d.StubPtr = &method_stub<T, TMethod>; // #1
		return d;
	}

	/**
	* Overloads the () operator (i.e. the function call(?) operator) so 
	* delegates can be used as my_delegate(); calls
	*/
	void operator()() const
	{
		return (*StubPtr)(ObjectReference);
	}
};

#endif