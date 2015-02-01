#include "Texture.h"
#include "stb.h"
#include "Vici.h"
#include "Platform.h"

Texture::Texture()
{
	_width = _height = _comp = 0;
	_texture = 0;
}

Texture::~Texture()
{

}

uint32 Texture::GetFormat(char* format)
{
	if (strcmp("rgb", format) == 0) return 3;
	else if (strcmp("rgba", format) == 0) return 4;
	else if (strcmp("grey", format) == 0) return 1;
	else if (strcmp("greyalpha", format) == 0) return 2;
	else return 0;	//return default
}

uint32 Texture::GetType(char* type)
{
	if (strcmp("2d", type) == 0) return GL_TEXTURE_2D;
	else if (strcmp("1d", type) == 0) return GL_TEXTURE_1D;
	else if (strcmp("3d", type) == 0) return GL_TEXTURE_3D;
	else return GL_TEXTURE_2D; //default assumed 2d
}

void Texture::LoadFromNode(rapidxml::xml_node<char>* node)
{
	//get node values
	char* path = node->first_node("path")->value();
	char* format = node->first_attribute("format")->value();
	char* type = node->first_node("type")->value();

	//convert path to releative platform friendly path
	char buff[BUFFER_SIZE];
	sprintf(buff, "%s/%s", _vici->GetCwd(), path);
	strcpy(buff, Platform_Pathify(buff));

	//load image
	unsigned char* image = stbi_load(buff, &_width, &_height, &_comp, GetFormat(format));

	//check if image was loaded
	if (image == NULL)
	{
		printf("Could not load texture at %s\n", path);
		return;
	}

	//set the texture type
	_type = GetType(type);

	//generate texture
	glGenTextures(1, &_texture);

	//bind it so we can set its properties
	glBindTexture(_type, _texture);

	//set some formats up
	uint32 glformat = 0;
	switch (_comp)
	{
	case 1:
		glformat = GL_RED;
		break;
	case 2:
		glformat = GL_RGB;
		break;
	case 3:
		glformat = GL_RGB;
		break;
	case 4:
		glformat = GL_RGBA;
		break;
	default:
		glformat = GL_RGB;
		break;
	}

	// Give the image to OpenGL
	glTexImage2D(_type, 0, glformat, _width, _height, 0, glformat, GL_UNSIGNED_BYTE, image);

	// Nice trilinear filtering.
	glTexParameteri(_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(_type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(_type);

	//bind default texture again
	glBindTexture(_type, 0);

	//free up on memory
	stbi_image_free(image);
}

void Texture::Bind()
{
	glBindTexture(_type, _texture);
}