#include <sstream>
#include <fstream>

// Creates the stream given the name
#define SerializationOutputStream(name, path) std::ofstream name(path)
#define SerializationInputStream(name, path) std::ifstream name(path)
#define SerializationStringStream(name, path) std::stringstream name

// For polymorphic uses
#include <cereal/types/polymorphic.hpp>

// Std library support
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>


// Creates an archive for serialization data using the given streem
#ifdef VICI_DEBUG
//#include <cereal/archives/json.hpp>

//#define ArchiveOut cereal::JSONOutputArchive
//#define ArchiveIn cereal::JSONInputArchive

#include <cereal/archives/xml.hpp>

#define ArchiveOut cereal::XMLOutputArchive
#define ArchiveIn cereal::XMLInputArchive

#define CreateOutputArchive(archiveName, streamName, path) SerializationOutputStream (streamName, path); \
														   ArchiveOut archiveName(streamName)

#define CreateInputArchive(archiveName, streamName, path) SerializationInputStream (streamName, path); \
															 ArchiveIn archiveName(streamName)

#else // ELSE - Release mode

#include <cereal/archives/portable_binary.hpp>

#define ArchiveOut cereal::PortableBinaryOutputArchive
#define ArchiveIn cereal::PortableBinaryInputArchive

#define CreateOutputArchive(archiveName, streamName, path) SerializationOutputStream (streamName, path); \
														   ArchiveOut archiveName(streamName)

#define CreateInputArchive(archiveName, streamName, path) SerializationInputStream (streamName, path); \
															 ArchiveIn archiveName(streamName)
#endif

// Generator for serialization
#define _SERIALIZE_VAR(var, arc) \
	try { \
		arc(cereal::make_nvp(#var,var)); \
	} \
	catch(cereal::Exception e) \
	{ } \
 

// Same as above but custom name
#define _SERIALIZE_VAR_NAME(var, name, arc) \
	try { \
		arc(cereal::make_nvp(name,var)); \
	} \
	catch(cereal::Exception e) \
	{ } \

// Serializes base class
#define _SERIALIZE_PARENT(Type, arc) _SERIALIZE_VAR_NAME(cereal::base_class<Type>(this), #Type, arc)