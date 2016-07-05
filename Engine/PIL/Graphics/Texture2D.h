#pragma once

#include "Texture.h"

class PIL_API VTexture2D : public VTexture
{
private:
	int32 Width;
	int32 Height;

public:

	VTexture2D(ETextureWrapMode wrapMode = WRAP_REPEAT);

	~VTexture2D();

	/** 
	 * Loads the specified image from file
	 */
	static VTexture2D* FromFile(const class VFilePath& filePath);

	// Binds the vertex buffer
	virtual bool Lock() override;

	// Sends the vertex data upto the GPU
	virtual void Unlock(bool freeClientMemory = false) override;

	// Where (0,0) == bottom left
	void SetPixel(int32 x, int32 y, uint8 r, uint8 g, uint8 b, uint8 a);

	// Setters
	inline void SetSize(int32 width, int32 height) { Width = width; Height = height; }
	inline void SetWidth(int32 width) { Width = width; }
	inline void SetHeight(int32 height) { Height = height; }

	// Getters
	inline int32 GetWidth() { return Width; }
	inline int32 GetHeight() { return Height; }
};