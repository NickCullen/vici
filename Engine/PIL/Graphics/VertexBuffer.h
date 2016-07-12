#pragma once

#include "Buffer.h"	// need to derive from VBuffer
#include "GraphicsTypes.h"
#include "GraphicsConstants.h"

// Forward decl
class VShader;

/**
* Info of an element in a vertex
*/
struct PIL_API VElementInfo
{
	const char* ShaderID;	// Name of input array in shader
	EPlatformType Type;		// What type is each component of this element?
	int8 NumOfComponents;	// How many components of said type are there in this element?
	bool Normalize;			// Should the values be normalized when sent to the GPU?

	VElementInfo() = default;

	// Constructor
	VElementInfo(const char* nameInShader, int8 numOfComponents, EPlatformType type = TYPE_FLOAT32, bool normalize = false)
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
struct PIL_API VVertexElement
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
class PIL_API VVertexBuffer : public VBuffer
{
private:
	
	VVertexElement Elements[MAX_ELEMENTS_PER_VERTEX];	// Array of elements

	int32 NumOfElements;	// Number of elements in this buffer object

	int32 VertexSize;	// Size per vertex

protected:
	virtual int32 GetSingleItemDataSize() override;

	virtual void SetSingleItemDataSize(int32 size) override;

public:
	VVertexBuffer(EBufferUse useage = STATIC_DRAW);
	~VVertexBuffer();

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

	// Set element array info in the shader
	void SetElementsInShader(VShader* shader);
};