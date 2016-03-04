#pragma once

#include "CoreAPI.h"
#include "VTypes.h"
#include "EngineConstants.h"

// Forward decl
class VShader;

// Typedefs
typedef uint32 VBO_t;


// Defines what type of buffer this is
enum EBufferType
{
	ARRAY_BUFFER,			// vertex data
	ELEMENT_BUFFER			// index data
};

// Defines how this buffer is to be used
enum EBufferUse
{
	STATIC_DRAW,		// Upload once - draw many times
	DYNAMIC_DRAW,		// Changed from time to time but drawn many more times than that
	STREAM_DRAW		// Vertex data will change almost every frame
};

// Type of value in an element
enum EElementType
{
	ELEM_TYPE_FLOAT,
	ELEM_TYPE_INT
};

/**
* Info of an element in a vertex
*/
struct CORE_API VElementInfo
{
	const char* ShaderID;	// Name of input array in shader
	EElementType Type;		// What type is each component of this element?
	int8 NumOfComponents;	// How many components of said type are there in this element?
	bool Normalize;			// Should the values be normalized when sent to the GPU?

	VElementInfo() = default;

	// Constructor
	VElementInfo(const char* nameInShader, int8 numOfComponents, EElementType type = ELEM_TYPE_FLOAT, bool normalize = false)
		:ShaderID(nameInShader),
		Type(type),
		NumOfComponents(numOfComponents),
		Normalize(normalize)
	{
	}
};

/**
 * Structure that holds info about each
 * interleaved element per vertex
 */
struct CORE_API VVertexElement
{
	int32 Size;				// Sizeof this element
	int32 Offset;			// Offset (in bytes) from the first element
	VElementInfo Info;	// Info about this info when binding it to the vertex array list
};

/**
 * Class for dynamic vertex buffers - General logic is as follows:
 * 1. Allocate each element per vertex using AddElement
 * 2. Pre-allocate space using AllocateVertices
 * 3. Lock the vertex buffer ready to upload data
 * 4. Add a vertex using AddVertex
 * 5. Fill in the currently add vertex using AddData and give in the 
 *    element ID you got from step 1.
 * 6. Unlock to send data to graphics card
 */
class CORE_API VVertexBuffer
{
private:
	
	void* Data;	// Vertex data in memory

	VVertexElement Elements[MAX_ELEMENTS_PER_VERTEX];	// Array of elements

	int32 NumOfElements;	// Number of elements in this buffer object

	int32 VertexSize;	// Size per vertex

	int32 Count;		// Number of vertices in this buffer object

	int32 Size;			// Current size in bytes of the buffer data

	int32 MaxSize;		// Allocated size in bytes of Data

	VBO_t VBO;	// Reference to the vertex buffer in gpu

	EBufferType Type;	// The type of vertex buffer

	EBufferUse Usage;	// How this buffer is to be used

	// Converts the Type value to 
	// its respective GLenum
	uint32 BufferTypeToGL();
	uint32 BufferUsageToGL();
	uint32 ElementTypeToGL(const EElementType type);

	// Resizes Data array to NewSize where NewSize = size in bytes of new array
	void Resize(int32 NewSize);
public:
	VVertexBuffer(EBufferType type = ARRAY_BUFFER, EBufferUse useage = STATIC_DRAW);
	~VVertexBuffer();

	// Binds the vertex buffer
	void Bind();

	// Creates the VBO and prepares for uploading vertices
	bool Lock();

	// Sends the vertex data upto the GPU
	void Unlock();

	// Frees the data held in client memory
	void FlushClientMemory();

	// Frees the data held on the GPU
	void FlushGPUMemory();

	// Frees all data
	void Flush();

	// Allocate space for specified number of vertices
	// Allocates data array to be VertexSize * Count
	void AllocateVertices(int32 Count);

	// Adds an element and returns the id of it
	template<typename T>
	int AddElement()
	{
		int32 SizeOfElement = sizeof(T);
		return AddElement(SizeOfElement);
	}

	// Actual AddElement implementation
	// If you want the SizeOfElement to not effect the VertexSize variable,
	// Pass in false to the last argument to this function
	int32 AddElement(int32 SizeOfElement, bool EffectVertexSize = true);

	// Sets element info with the given id
	void SetElementInfo(int32 id, const VElementInfo& info);

	// Adds 1 to the Count
	void AddVertex();

	// Add the data to the vertex
	template <typename T>
	void AddData(const T& data, int32 elementID)
	{
		AddData((const void*)&data, elementID);
	}

	void AddData(const void* data, int32 elementID);

	// Sets the data from an array
	void FromArray(void* data, int32 size, int32 sizePerVertex);

	// Set element array info in the shader
	void SetElementsInShader(VShader* shader);
};