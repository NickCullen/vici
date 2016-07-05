#pragma once

#include "PIL/PILAPI.h"

/**
* Helper class for loading a text file in one go (used heavily in the XML Document loader)
*/

class PIL_API VTextFile
{
public:
	char* Text; /**< char poitner pointing to the text files text in memory */

	/**
	* TextFile constructor 
	* @param path the path to the text file to load (note this will load the file)
	*/
	VTextFile(const class VFilePath& path);

	/**
	* Text file destrucor (will free memory if file was loaded)
	*/
	~VTextFile();

	/**
	* cast operator to cast this text file into a char* pointer
	* note that the file may not be loaded so may return NULL
	* @return Pointer to the text in memory (maybe NULL if file was not loaded)
	*/
	operator char*()
	{
		return Text;
	}

	/**
	* cast operator to cast this text file into a char* pointer
	* note that the file may not be loaded so may return NULL
	* @return Pointer to the text in memory (maybe NULL if file was not loaded)
	*/
	operator const char*()
	{
		return (const char*)Text;
	}

	
	/**
	* Checks if the file is loaded or not
	* @return boolean true if text file was loaded false if not
	*/
	bool IsLoaded();
};
