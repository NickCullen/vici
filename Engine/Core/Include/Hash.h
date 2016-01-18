#ifndef HASH_H
#define HASH_H

#include "PlatformDefinitions.h"
#include "CoreAPI.h"
#include "Serialization.h"

//the typedef for a hash
typedef uint32 hash_int;

/**
* This class is used to optimize the comparison between 2 strings 
* It will take a string (char*) and covert it into an unsigned integer
* This makes comparison between 2 strings (i.e. 2 hashes) a simple integer check 
* status (complete)
*/

class CORE_API Hash
{
private:
	hash_int Value; /**< the output of the hash string (representing a string as an integer */

#ifdef VICI_DEBUG
	std::string Friendly; /**< Friendly representation of hash */
#endif

public:
	/**
	* VHash destructor 
	*/
	~Hash();

	/**
	* Default vhash constructor
	*/
	Hash();
	
	//virtual void Serialize(ArchiveOut& archive);
	//virtual void Deserialize(ArchiveIn& archive);
	
	template<class Archive>
	void serialize(Archive& ar)
	{
		_SERIALIZE_VAR(Value, ar)

#ifdef VICI_DEBUG
		_SERIALIZE_VAR(Friendly,ar)
#endif
	}

	// Typical overloads
	bool operator <  (const Hash &other) const { return Value <  other.Value; }
	bool operator >	 (const Hash &other) const { return Value >  other.Value; }
	bool operator <= (const Hash &other) const { return Value <= other.Value; }
	bool operator >= (const Hash &other) const { return Value >= other.Value; }
	bool operator == (const Hash &other) const { return Value == other.Value; }
	bool operator != (const Hash &other) const { return Value != other.Value; }

	/**
	* Copy constructor for VHash
	* @param other The VHash being copied 
	*/
	Hash(const Hash& other);
	/**
	* Overloaded constructor taking a string to set _hash
	* @param str string to hash
	*/
	Hash(const char* str);
	/**
	* Another overloaded constructor taking const char* to avoid errors of casting 
	* from char* to const char* and vis versa
	* @param str string to hash
	*/
	Hash(char* str);

	/**
	* equality comparison between this hash and an integer
	* @param other integer 
	* @return returns true if equal false if not
	*/
	bool operator==(hash_int other);

	/**
	* equality comparison between this hash and a string
	* note that this will hashify the string first so it isnt quick
	* @param the string to be hashified and checked against
	* @return returns true if equal false if not
	*/
	bool operator==(const char* other);
	/**
	* equality comparison between this hash and a string
	* note that this will hashify the string first so it isnt quick
	* @param the string to be hashified and checked against
	* @return returns true if equal false if not
	*/
	bool operator==(char* other);

	/**
	* !equality comparison between this hash and an integer
	* @param other integer
	* @return returns true if not equal false if so
	*/
	bool operator!=(hash_int other);

	/**
	* !equality comparison between this hash and a string
	* note that this will hashify the string first so it isnt quick
	* @param the string to be hashified and checked against
	* @return returns true if not equal false if so
	*/
	bool operator!=(const char* other);
	/**
	* !equality comparison between this hash and a string
	* note that this will hashify the string first so it isnt quick
	* @param the string to be hashified and checked against
	* @return returns true if not equal false if so
	*/
	bool operator!=(char* other);

	/** 
	* Sets this hash from an int
	* @param eq the integer to set this _hash value to
	* @return returns (*this)
	*/
	Hash operator=(hash_int eq);
	/**
	* Sets this hash from a string (note this will Hashify the string first)
	* @param eq the string to hashify then set this _hash value to
	* @return returns (*this)
	*/
	Hash operator=(const char* eq);
	/**
	* Sets this hash from a string (note this will Hashify the string first)
	* @param eq the string to hashify then set this _hash value to
	* @return returns (*this)
	*/
	Hash operator=(char* eq);

	/** 
	* checks if this hash is less than the other 
	* @param other Checks if this is less than an integer
	* @return returns true if less then false if not
	*/
	bool operator<(hash_int other);

	/**
	* checks if this hash is less than the other
	* @param other Checks if this is less than an a string (note this string will
	* be hashified first so it isn't too quick
	* @return returns true if less then false if not
	*/
	bool operator<(const char* other);
	/**
	* checks if this hash is less than the other
	* @param other Checks if this is less than an a string (note this string will
	* be hashified first so it isn't too quick
	* @return returns true if less then false if not
	*/
	bool operator<(char* other);

	/**
	* checks if this hash is greater than the other
	* @param other Checks if this is greater than an integer
	* @return returns true if greater then false if not
	*/
	bool operator>(hash_int other);

	/**
	* checks if this hash is greater than the other
	* @param other Checks if this is greater than an a string (note this string will
	* be hashified first so it isn't too quick
	* @return returns true if greater then false if not
	*/
	bool operator>(const char* other);
	/**
	* checks if this hash is greater than the other
	* @param other Checks if this is greater than an a string (note this string will
	* be hashified first so it isn't too quick
	* @return returns true if greater then false if not
	*/
	bool operator>(char* other);

	/**
	* Get function to return the hash value
	* @return returns the integer value of the hash
	*/
	inline const hash_int GetValue() const
	{
		return Value;
	}

	/**
	* Static function which takes a string and hashifies it into 
	* a single integer
	* @param str The string that requires hashing
	* @return Returns the hash value (integer) of the string
	*/
	static inline hash_int Hashify(const char* str)
	{
		hash_int hash = 2166136261;

		while (*str)
		{
			hash ^= *str++;
			hash *= 16777619;
		}

		return hash;
	}
};

/*namespace std
{
	// forward decl
	//template <class T> struct hash;

	template <> 
	struct hash<VHash>
	{
		typedef VHash argument_type;

		size_t operator()(VHash const & val) const
		{
			return val.Value();
		}
	};
}*/

#endif
