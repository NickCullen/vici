#include <sstream>
#include <fstream>

// Creates the stream given the name
#define SerializationOutputStream(name, path) std::ofstream name(path);
#define SerializationInputStream(name, path) std::ifstream name(path);
#define SerializationStringStream(name, path) std::stringstream name;

// Std library support
#include <cereal/types/string.hpp>

// Creates an archive for serialization data using the given streem
#ifdef VICI_DEBUG
#include <cereal/archives/json.hpp>

#define ArchiveOut cereal::JSONOutputArchive
#define ArchiveIn cereal::JSONInputArchive

#define CreateOutputArchive(name, stream) ArchiveOut name(stream);
#define CreateInputArchive(name, stream) ArchiveIn name(stream);

#else // ELSE - Release mode

#include <cereal/archives/portable_binary.hpp>

#define ArchiveOut cereal::PortableBinaryOutputArchive
#define ArchiveIn cereal::PortableBinaryInputArchive

#define CreateOutputArchive(name, stream) ArchiveOut name(stream);
#define CreateInputArchive(name, stream) ArchiveIn name(stream);
#endif

// Generator for serialization
#define _SERIALIZE_VAR(var, arc) arc(cereal::make_nvp(#var,var))

// Generator for deserialization 
#define _DESERIALIZE_VAR(var, arc) arc(cereal::make_nvp(#var,var))

#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

// Pure virtual interface for serialization / deserialization
class ISerializable
{
public:
	
    virtual void Serialize(ArchiveOut& archive) = 0;
    virtual void Deserialize(ArchiveIn& archive) = 0;
    
};

#endif