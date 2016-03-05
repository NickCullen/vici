#include "Texture2D.h"
#include "Glew.h"
#include "FilePath.h"

// Image loading
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

VTexture2D::VTexture2D(ETextureWrapMode wrapMode)
{

}

VTexture2D::~VTexture2D()
{

}

// Binds the vertex buffer
bool VTexture2D::Lock()
{
	if (!VTexture::Lock())
		return false;

	glBindTexture(GL_TEXTURE_2D, Handle);

	return true;
}

VTexture2D* VTexture2D::FromFile(const VFilePath& filePath)
{
	int comp, width, height;

	stbi_uc* pixels = stbi_load(filePath.GetString(), &width, &height, &comp, 0);

	// if loaded
	if (pixels)
	{
		EColorMode colorMode = ComponentCountToColorMode(comp);	//Color mode of the texture

		VTexture2D* tex = new VTexture2D();
		if (tex->Lock())
		{
			tex->Width = width;
			tex->Height = height;
			tex->InternalFormat = colorMode;
			tex->PixelFormat = colorMode;
			tex->PixelDataType = ELEM_TYPE_UINT8;
			tex->GenerateMipMap = true;
			
			tex->Pixels = new stbi_uc[width*height*comp];
			memcpy(tex->Pixels, pixels, width*height*comp*sizeof(stbi_uc));

			tex->Unlock();	
		}
		// Error creating texture
		else
		{
			delete (tex);
			tex = nullptr;
		}

		// Free image data
		stbi_image_free(pixels);

		return tex;
	}
	
	return nullptr;
}

// Sends the vertex data upto the GPU
void VTexture2D::Unlock(bool freeClientMemory)
{
	uint32 wrapMode = WrapModeToGL(WrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterMethodToGL(MinFilterMethod));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterMethodToGL(MagFilterMethod));


	glTexImage2D(GL_TEXTURE_2D,				// Type of texture
		GenerateMipMap ? LOD : 0,			// Level of Detail (from mip)
		ColorModeToGL(InternalFormat),		// Format pixel data is on gpu
		Width, Height,						// Size
		0,									// Specification says this has to be 0
		ColorModeToGL(PixelFormat),			// Format of pixel data in Pixels array
		ElementTypeToGL(PixelDataType),		// Type of pixel (float/byte etc.)
		Pixels								// Array of pixels
	);

	// Generate mips if needed
	if (GenerateMipMap)
		glGenerateMipmap(TextureTypeToGL(Type));

	// Free RAM space if requested
	if (freeClientMemory)
		FlushClientMemory();

	
}