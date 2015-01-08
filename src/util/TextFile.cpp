#include "TextFile.h"
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

TextFile::TextFile(const char* path)
{
	_text = NULL;
	FILE* f = fopen(path, "rb");
	if (f)
	{
		//seek the last byte of the file
		fseek(f, 0, SEEK_END);
		//offset from the first to the last byte, or in other words, filesize
		int size = ftell(f);
		//go back to the start of the file
		rewind(f);

		//allocate a string that can hold it all
		_text = new char[size + 1];

		//read it all in one operation
		int read_size = fread(_text, sizeof(char), size, f);
		//fread doesnt set it so put a \0 in the last position
		//and buffer is now officialy a string
		_text[size] = '\0';

		if (size != read_size) {
			//something went wrong, throw away the memory and set
			//the buffer to NULL
			delete(_text);
			_text = NULL;
		}

		fclose(f);
	}
}

TextFile::~TextFile()
{
	if (_text != NULL)
	{
		delete(_text);
	}
}

bool TextFile::IsLoaded()
{
	return (_text != NULL);
}