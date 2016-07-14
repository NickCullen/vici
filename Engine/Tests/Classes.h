#pragma once

#include "Core/EngineIncludes.h"



class TestSerializationClass
{
public:
	int x;

	float y;

	VString name;

	VArray<VString> MyArray;

	TestSerializationClass()
	{
		x = 5;
		y = 42.66f;
		name = "ThisIsMyName";

		MyArray.push_back(VString("String1"));
		MyArray.push_back(VString("String2"));
		MyArray.push_back(VString("String3"));
		MyArray.push_back(VString("String4"));
	}

	template< class Archive >
	void serialize(Archive & ar)
	{
		ar(CEREAL_NVP(x), CEREAL_NVP(y), CEREAL_NVP(name), CEREAL_NVP(MyArray));
	}
};


#define Object_MEMBERS(_GEN_) \
	_GEN_(int32, ObjectID)

class Object
{
public:
	_CLASS_DEF_NO_SUPER_(Object)

	Object()
	{
		Object_MEMBERS(_DEFAULT_MEMBERS_)
	}

	Object(const Object& other)
	{
		Object_MEMBERS(_COPY_MEMBERS_)
	}

	/**
	 * Simply instantiates a shared pointer to an Object with specified type
	 * @Return Shared pointer to newly instantiated object
	 */
	template<typename T>
	static inline VSharedPointer<T> Instantiate()
	{
		return std::make_shared<T>();
	}

	/**
	 * Instanties a new Object of specified Type with the added feature of 
	 * Copying the contents of the 'other' object
	 * @param other The object who will be copied from
	 * @return a new instance of T copied from 'other'
	 */
	template<typename T>
	static inline VSharedPointer<T> Instantiate(VSharedPointer<T>& other)
	{
		VSharedPointer<T> ret;
		PlatformTypeToCode<VSharedPointer<T>>::Copy(ret, other);
		return ret;
	}

};





#define GameObject_MEMBERS(_GEN_) \
	_GEN_(VArray<VSharedPointer<GameObject>>, Children)


class GameObject : public Object
{
public:	
	typedef Object Super;	
	
	GameObject_MEMBERS(_DECL_MEMBERS_)
	
	template <class Archive>	
	void serialize(Archive& ar)	
	{	
		cereal::prologue(ar, Name);

		Super::serialize(ar);	
		GameObject_MEMBERS(_SERIALIZE_MEMBERS_)
	}	
	
	void CopyFrom(GameObject& other)
	{	
		Super::CopyFrom(other);	
		GameObject_MEMBERS(_COPY_MEMBERS_)
	}	

public:
	
	VString Name;

	GameObject()
		: Super()
	{
		
		GameObject_MEMBERS(_DEFAULT_MEMBERS_)

	}

	GameObject(const GameObject& other)
		: Super(other)
	{
		GameObject_MEMBERS(_COPY_MEMBERS_)

	}
};



