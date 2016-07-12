#pragma once

#include <stdint.h>
#include "PIL/Collections/SharedPointer.h"
#include "PIL/Collections/Array.h"

#if VICI_OPENGL
#include "PIL/Graphics/OpenGL/Include/Glew.h"
#endif

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float float32;
typedef double float64;

/**
 * Specialised Templates around types for quick access
 */

enum EPlatformType
{
	TYPE_VOID,

	TYPE_SHARED_POINTER,

	TYPE_ARRAY,

	TYPE_INT8,
	TYPE_INT16,
	TYPE_INT32,
	TYPE_INT64,

	TYPE_UINT8,
	TYPE_UINT16,
	TYPE_UINT32,
	TYPE_UINT64,

	TYPE_FLOAT32,

	TYPE_FLOAT64,
};

/**
 * Specialised templates
 */
template <class C>
struct PlatformTypeToCode
{
	enum { Code = TYPE_VOID };

	inline static C DefaultValue()
	{
		return C();
	}

	inline static void Copy(C& lhs, const C& rhs)
	{
		lhs = rhs;
	}

#ifdef VICI_OPENGL
	enum {OPENGL_TYPE = GL_FLOAT };		// Assume float
#endif
};


/**
 * For shared pointer types
 */
template <typename T>
struct PlatformTypeToCode<VSharedPointer<T>>
{
	enum { Code = TYPE_SHARED_POINTER };

	inline static VSharedPointer<T> DefaultValue()
	{
		return VSharedPointer<T>();
	}

	inline static void Copy(VSharedPointer<T>& lhs, const VSharedPointer<T>& rhs)
	{
		lhs = std::make_shared<T>(*rhs);
	}

};

/**
 * Array type
 */
template <typename T>
struct PlatformTypeToCode<VArray<T>>
{
	enum { Code = TYPE_ARRAY };

	inline static VArray<T> DefaultValue()
	{
		return VArray<T>();
	}

	inline static void Copy(VArray<T>& lhs, const VArray<T>& rhs)
	{
		lhs = VArray<T>(rhs.size());
		for (uint32 i = 0; i < rhs.size(); i++)
			PlatformTypeToCode<T>::Copy(lhs[i], rhs[i]);
	}

};

/**
* Int8
*/
template <>
struct PlatformTypeToCode<int8>
{
	enum { Code = TYPE_INT8 };

	inline static int8 DefaultValue()
	{
		return 0;
	}

	inline static void Copy(int8& lhs, const int8& rhs)
	{
		lhs = rhs;
	}
#ifdef VICI_OPENGL
	enum { OPENGL_TYPE = GL_BYTE };
#endif
};

/**
* Int16
*/
template <>
struct PlatformTypeToCode<int16>
{
	enum { Code = TYPE_INT16 };

	inline static int16 DefaultValue()
	{
		return 0;
	}

	inline static void Copy(int16& lhs, const int16& rhs)
	{
		lhs = rhs;
	}
#ifdef VICI_OPENGL
	enum { OPENGL_TYPE = GL_SHORT };
#endif
};

/**
* Int32
*/
template <>
struct PlatformTypeToCode<int32>
{
	enum { Code = TYPE_INT32 };

	inline static int32 DefaultValue()
	{
		return 0;
	}

	inline static void Copy(int32& lhs, const int32& rhs)
	{
		lhs = rhs;
	}
#ifdef VICI_OPENGL
	enum { OPENGL_TYPE = GL_INT };
#endif
};

/**
* Int64
*/
template <>
struct PlatformTypeToCode<int64>
{
	enum { Code = TYPE_INT64 };

	inline static int64 DefaultValue()
	{
		return 0;
	}

	inline static void Copy(int64& lhs, const int64& rhs)
	{
		lhs = rhs;
	}

#ifdef VICI_OPENGL
	enum { OPENGL_TYPE = GL_INT };		// Not supported - default to int32
#endif
};

// Unsigned -----

/**
* UInt8
*/
template <>
struct PlatformTypeToCode<uint8>
{
	enum { Code = TYPE_UINT8 };

	inline static uint8 DefaultValue()
	{
		return 0;
	}

	inline static void Copy(uint8& lhs, const uint8& rhs)
	{
		lhs = rhs;
	}

#ifdef VICI_OPENGL
	enum { OPENGL_TYPE = GL_UNSIGNED_BYTE };
#endif
};

/**
* UInt16
*/
template <>
struct PlatformTypeToCode<uint16>
{
	enum { Code = TYPE_UINT16 };

	inline static uint16 DefaultValue()
	{
		return 0;
	}

	inline static void Copy(uint16& lhs, const uint16& rhs)
	{
		lhs = rhs;
	}

#ifdef VICI_OPENGL
	enum { OPENGL_TYPE = GL_UNSIGNED_SHORT };
#endif
};

/**
* UInt32
*/
template <>
struct PlatformTypeToCode<uint32>
{
	enum { Code = TYPE_UINT32 };

	inline static uint32 DefaultValue()
	{
		return 0;
	}

	inline static void Copy(uint32& lhs, const uint32& rhs)
	{
		lhs = rhs;
	}

#ifdef VICI_OPENGL
	enum { OPENGL_TYPE = GL_UNSIGNED_INT };
#endif
};

/**
* UInt64
*/
template <>
struct PlatformTypeToCode<uint64>
{
	enum { Code = TYPE_UINT64 };

	inline static uint64 DefaultValue()
	{
		return 0;
	}

	inline static void Copy(uint64& lhs, const uint64& rhs)
	{
		lhs = rhs;
	}

#ifdef VICI_OPENGL
	enum { OPENGL_TYPE = GL_UNSIGNED_INT };		// Not supported - default to uint32
#endif
};

// Floats & Doubles -----


/**
 * Float32
 */
template<>
struct PlatformTypeToCode<float32>
{
	enum { Code = TYPE_FLOAT32 };

	inline static float32 DefaultValue()
	{
		return 0.0f;
	}

	inline static void Copy(float32& lhs, const float32& rhs)
	{
		lhs = rhs;
	}

#ifdef VICI_OPENGL
	enum { OPENGL_TYPE = GL_FLOAT };
#endif
};

/**
 * Float 64
 */
template<>
struct PlatformTypeToCode<float64>
{
	enum { Code = TYPE_FLOAT64 };

	inline static float64 DefaultValue()
	{
		return 0.0;
	}

	inline static void Copy(float64& lhs, const float64& rhs)
	{
		lhs = rhs;
	}

#ifdef VICI_OPENGL
	enum { OPENGL_TYPE = GL_DOUBLE };
#endif
};