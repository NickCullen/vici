#include "PIL/Graphics/Texture2D.h"
#include "Glew.h"
#include "PIL/FileSystem/FilePath.h"
#include "GLTypeConverters.h"

// Image loading
#define STB_IMAGE_IMPLEMENTATION
#include "PIL/Graphics/stb_image.h"

VTexture2D::VTexture2D(ETextureWrapMode wrapMode)
	:VTexture(TEXTURE_2D),
	Width(0),
	Height(0)
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

	stbi_set_flip_vertically_on_load(1);	// stb loads images upside down

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
		GLTypeConverter::ColorModeToGL(InternalFormat),		// Format pixel data is on gpu
		Width, Height,						// Size
		0,									// Specification says this has to be 0
		GLTypeConverter::ColorModeToGL(PixelFormat),			// Format of pixel data in Pixels array
		GLTypeConverter::ElementTypeToGL(PixelDataType),		// Type of pixel (float/byte etc.)
		Pixels								// Array of pixels
	);

	// Generate mips if needed
	if (GenerateMipMap)
		glGenerateMipmap(TextureTypeToGL(Type));

	// Free RAM space if requested
	if (freeClientMemory)
		FlushClientMemory();

	
}

void VTexture2D::SetPixel(int32 x, int32 y, uint8 r, uint8 g, uint8 b, uint8 a)
{
	stbi_uc* u8 = ((stbi_uc*)Pixels);	// Convert pixels to uint8 first
	int32 index = 0; 

	switch (PixelFormat)
	{
		case COLOR_GREYSCALE:
		{
			index = ((y*Width) + x);
			u8[index] = r;
			break;
		}
		case COLOR_GREY_ALPHA:
		{
			index = ((y*Width) + x) * 2;
			u8[index] = r;
			u8[index+1] = g;
			break;
		}

		case COLOR_RGB:
		{
			index = ((y*Width) + x) * 3;
			u8[index] = r;
			u8[index+1] = g;
			u8[index+2] = b;
			break;
		}

		case COLOR_RGBA:
		{
			index = ((y*Width) + x) * 4;
			u8[index] = r;
			u8[index+1] = g;
			u8[index+2] = b;
			u8[index+3] = a;
			break;
		}

		// Assume RGB
		default:
		{
			index = ((y*Width) + x) * 3;
			u8[index] = r;
			u8[index + 1] = g;
			u8[index + 2] = b;

			break;
		}
	}
	
}