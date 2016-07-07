#pragma once

#include "PIL/PILAPI.h"
#include "PIL/DataTypes/PlatformTypes.h"
#include "MaterialParam.h"
#include "GraphicsTypes.h"

// Non-public abi texture handle
struct VInternalTextureHandle;

/**
 * Base class for textures
 */
class PIL_API VTexture : public IMaterialParam
{
protected:
	static int32 ActiveTextureCount;		// Number of currently active textures

	void* Pixels;		// Pixel data

	VInternalTextureHandle* Handle;	// Handle to the texture on the gpu

	ETextureType Type;

	ETextureWrapMode WrapMode;

	ETextureFilterMethod MinFilterMethod;	// Happens when image is scaled down

	ETextureFilterMethod MagFilterMethod;	// Happens when Image is scaled up

	EColorMode InternalFormat;		// Format pixels stored on the GPU

	EColorMode PixelFormat;			// Format of pixels in Pixels array

	EElementType PixelDataType;		// What type of data are the pixel elements?

	int32 LOD;	// Level of detail
	
	bool GenerateMipMap;				//Should mipmap be generated for this texture?

	// Converts the number of components to its relevant EColorMode
	static EColorMode ComponentCountToColorMode(int8 count);

	// Returns the number of components in the EColorMode
	static int8 ComponentsInColorMode(EColorMode mode);
	int8 ComponentsInColorMode();	// non static version
public:
	VTexture(ETextureType type = TEXTURE_2D, ETextureWrapMode wrapMode = WRAP_REPEAT);

	virtual ~VTexture();

	// Make this texture active
	// Pass in an integer if you want to bind it to an active texture
	// other than texture0
	void Bind(int32 activeTextureNum = 0);

	// Sets to default texture
	void Unbind();

	// Prepares the texture for uploading to the 
	// GPU. Call before editing pixel data.
	// Binds the vertex buffer
	bool Lock();

	// Sends the vertex data upto the GPU
	// Solely upto the derived class to handle what happens when
	// uploading to the GPU
	// Pass in true to delete Pixel array in RAM
	virtual void Unlock(bool freeClientMemory = false) = 0;

	// Frees the data held in client memory
	void FlushClientMemory();

	// Frees the data held on the GPU
	void FlushGPUMemory();

	// Frees all data
	void Flush();

	// RGBA colour for border
	void SetBorderColor(const class Vector4f& color);

	// fitler methods
	void SetMinFilterMetho(ETextureFilterMethod method);
	void SetMagFilterMetho(ETextureFilterMethod method);

	// Loads pixels from array
	void FromArray(void* pixels, int32 sizeInBytes);

	// Implements IMaterialParam interface
	virtual bool SendToShader(struct VShaderInputHandle* handle) override;
	virtual void CleanupFromShader() override;

	// Setters
	inline void SetGenerateMipmap(bool setMipmap) { GenerateMipMap = setMipmap; }
	inline void SetInternalFormat(EColorMode mode) { InternalFormat = mode; }
	inline void SetPixelFormat(EColorMode mode) { PixelFormat = mode; }
	inline void SetPixelDataType(EElementType type) { PixelDataType = type; }
};