#include "PIL/FileSystem/TextFile.h"
#include "PIL/FileSystem/FilePath.h"
#include <stdio.h>

VTextFile::VTextFile(const VFilePath& path)
	:Text(nullptr)
{
	FILE* f = fopen(path.GetString(), "rb");
	if (f)
	{
		//seek the last byte of the file
		fseek(f, 0, SEEK_END);
		//offset from the first to the last byte, or in other words, filesize
		int size = ftell(f);
		//go back to the start of the file
		rewind(f);

		//allocate a string that can hold it all
		Text = new char[size + 1];

		//read it all in one operation
		size_t read_size = fread(Text, sizeof(char), size, f);
		//fread doesnt set it so put a \0 in the last position
		//and buffer is now officialy a string
		Text[size] = '\0';

		if (size != read_size) {
			//something went wrong, throw away the memory and set
			//the buffer to NULL
			delete(Text);
			Text = NULL;
		}

		fclose(f);
	}
}

VTextFile::~VTextFile()
{
	if (Text != nullptr)
	{
		delete [] Text;
	}
}

bool VTextFile::IsLoaded()
{
	return (Text != nullptr);
}