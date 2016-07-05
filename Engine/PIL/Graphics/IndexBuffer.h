#pragma once

#include "Buffer.h"

/** 
 * Defines what index type an index array 
 * draws its vertices
 */
enum EIndexType
{
	INDEX_TYPE_POINTS,
	INDEX_TYPE_LINES,
	INDEX_TYPE_LINE_LOOP,
	INDEX_TYPE_LINE_STRIP,
	INDEX_TYPE_TRIANGLES,
	INDEX_TYPE_TRIANGLE_STRIP,
	INDEX_TYPE_TRIANGLE_FAN,
	INDEX_TYPE_QUADS,
	INDEX_TYPE_QUAD_STRIP,
	INDEX_TYPE_POLYGON 
};

/**
 * Buffer which contain indices into a vertex buffer
 */
class PIL_API VIndexBuffer : public VBuffer
{
private:
	EIndexType IndexType;	// Type of faces this index buffer draws in

	// Converts FaceType to relevant GLEnum
	uint32 IndexTypeToGL();
protected:
	virtual int32 GetSingleItemDataSize() override;

	virtual void SetSingleItemDataSize(int32 size) override;
public:

	VIndexBuffer(EIndexType faceType = INDEX_TYPE_TRIANGLES, EBufferUse usage = STATIC_DRAW);

	~VIndexBuffer();

	void DrawElements();
};