#pragma once

#include "Texture.h"

class CORE_API VTexture2D : public VTexture
{
private:
	int32 Width;
	int32 Height;

public:

	VTexture2D(ETextureWrapMode wrapMode = WRAP_REPEAT);

	~VTexture2D();

	// Binds the vertex buffer
	virtual bool Lock() override;

	// Sends the vertex data upto the GPU
	virtual void Unlock(bool freeClientMemory = false) override;

	// Setters
	inline void SetSize(int32 width, int32 height) { Width = width; Height = height; }
	inline void SetWidth(int32 width) { Width = width; }
	inline void SetHeight(int32 height) { Height = height; }
};