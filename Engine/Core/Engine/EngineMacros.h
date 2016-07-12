#pragma once

// Changes whatever value the input is at compile time
// to a const char* (string)
#define ItemToString(item) #item

/**
* Declares the class member veriables
*/
#define _DECL_MEMBERS_(TYPE, NAME) TYPE NAME;

/**
 * Sets all member vars to their default value
 */
#define _DEFAULT_MEMBERS_(TYPE, NAME) NAME = PlatformTypeToCode<TYPE>::DefaultValue();

/**
 * Serializes a member
 */
#define _SERIALIZE_MEMBERS_(TYPE, NAME) ar(cereal::make_nvp(#NAME, NAME));

/**
 * Copys from an object POINTER called 'other'
 */
#define _COPY_MEMBERS_(TYPE, NAME) PlatformTypeToCode<TYPE>::Copy(NAME, other.NAME);


/**
 * Definition for a class with a Base type
 */
#define _CLASS_DEF_WITH_SUPER_(ClassType, SuperType)	\
	public:	\
		typedef SuperType Super;	\
	\
	ClassType##_MEMBERS(_DECL_MEMBERS_)	\
	\
	template <class Archive>	\
	void serialize(Archive& ar)	\
	{	\
		Super::serialize(ar);	\
		ClassType##_MEMBERS(_SERIALIZE_MEMBERS_)	\
	}	\
	\
	void CopyFrom(ClassType& other)	\
	{	\
		Super::CopyFrom(other);	\
		ClassType##_MEMBERS(_COPY_MEMBERS_)	\
	}	


 /**
 * Definition for a class without a Base type
 */
#define _CLASS_DEF_NO_SUPER_(ClassType)	\
	public:	\
	ClassType##_MEMBERS(_DECL_MEMBERS_)	\
	\
	template <class Archive>	\
	void serialize(Archive& ar)	\
	{	\
		ClassType##_MEMBERS(_SERIALIZE_MEMBERS_)	\
	}	\
	\
	void CopyFrom(ClassType& other)	\
	{	\
		ClassType##_MEMBERS(_COPY_MEMBERS_)	\
	}	