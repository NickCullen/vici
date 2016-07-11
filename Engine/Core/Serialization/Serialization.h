#pragma once

#include "Core/CoreAPI.h"
#include "Core/Engine/Singleton.h"
#include "PIL/FileSystem/FilePath.h"

// Serialization in Vici uses third party library 'Cereal'
// For more info, see http://uscilab.github.io/cereal/

#include <cereal/cereal.hpp>

// NOTE:: Editor should use Xml, releease should use binary
// Will come back to this later when I have a nice build system
// from within the editor. but for now everything will be xml based.
#include <cereal/archives/xml.hpp>

// Streams for reading / writing data
#include <fstream>

// Serialization methods for std types
#include <cereal/types/vector.hpp>

// Type of input archive (differs betwen release/debug)
#define INPUT_ARCHIVE_TYPE XMLInputArchive

// Type of output archive (differents between release/debug)
#define OUTPUT_ARCHIVE_TYPE XMLOutputArchive


/**
 * Helper class to quickly serialize to / deserialize from 
 * files.
 */
class CORE_API VSerialization : VSingleton<VSerialization>
{
public:

	/**
	 * Ctor
	 */
	VSerialization() : VSingleton(this) {}

	/**
	 * Dtor
	 */
	~VSerialization() {}

	/**
	 * Loads an object from the given file
	 * @param obj The object to load (deserialize)
	 * @param filePath The file path containing the file with the given objects stats
	 */
	template <typename T>
	static inline void LoadObject(T& obj, VFilePath& filePath)
	{
		std::ifstream is(filePath.GetString(), std::ios::binary);
		cereal::INPUT_ARCHIVE_TYPE archive(is);

		archive(obj);
	}

	/**
	* Saves the given object to the specified file
	* @param obj The object to save (serialize)
	* @param filePath The file path to the location we want to save
	*/
	template <typename T>
	static inline void SaveObject(T& obj, VFilePath& filePath)
	{
		std::ofstream os(filePath.GetString(), std::ios::binary);
		cereal::OUTPUT_ARCHIVE_TYPE archive(os);

		archive(obj);
	}

	/**
	 * Creates the object and then loads it from a file, thus
	 * returning a pointer to it.
	 * @param filePath filepath to the file contaning the objects data
	 * @return Pointer to the created object
	 */
	template <typename T>
	static inline T* CreateAndLoadObject(VFilePath& filePath)
	{
		T* ret = new T;
		LoadObject(*ret, filePath);
		return ret;
	}
};