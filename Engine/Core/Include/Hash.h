#pragma once

#include "CoreAPI.h"
#include "VTypes.h"

//the typedef for a hash
typedef uint32 vhash_int;

/**
* This class is used to optimize the comparison between 2 strings 
* It will take a string (char*) and covert it into an unsigned integer
* This makes comparison between 2 strings (i.e. 2 hashes) a simple integer check 
* status (complete)
*/

class CORE_API VHash
{
private:
	vhash_int _hash; /**< the output of the hash string (representing a string as an integer */
public:
	/**
	* VHash destructor 
	*/
	~VHash();

	/**
	* Default vhash constructor
	*/
	VHash();

	// Typical overloads
	bool operator <  (const VHash &other) const { return _hash <  other._hash; }
	bool operator >	 (const VHash &other) const { return _hash >  other._hash; }
	bool operator <= (const VHash &other) const { return _hash <= other._hash; }
	bool operator >= (const VHash &other) const { return _hash >= other._hash; }
	bool operator == (const VHash &other) const { return _hash == other._hash; }
	bool operator != (const VHash &other) const { return _hash != other._hash; }

	/**
	* Copy constructor for VHash
	* @param other The VHash being copied 
	*/
	VHash(const VHash& other);
	/**
	* Overloaded constructor taking a string to set _hash
	* @param str string to hash
	*/
	VHash(const char* str);
	/**
	* Another overloaded constructor taking const char* to avoid errors of casting 
	* from char* to const char* and vis versa
	* @param str string to hash
	*/
	VHash(char* str);

	/**
	* equality comparison between this hash and an integer
	* @param other integer 
	* @return returns true if equal false if not
	*/
	bool operator==(vhash_int other);

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
	bool operator!=(vhash_int other);

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
	VHash operator=(vhash_int eq);
	/**
	* Sets this hash from a string (note this will Hashify the string first)
	* @param eq the string to hashify then set this _hash value to
	* @return returns (*this)
	*/
	VHash operator=(const char* eq);
	/**
	* Sets this hash from a string (note this will Hashify the string first)
	* @param eq the string to hashify then set this _hash value to
	* @return returns (*this)
	*/
	VHash operator=(char* eq);

	/** 
	* checks if this hash is less than the other 
	* @param other Checks if this is less than an integer
	* @return returns true if less then false if not
	*/
	bool operator<(vhash_int other);

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
	bool operator>(vhash_int other);

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
	inline const vhash_int Value() const
	{
		return _hash;
	}

	/**
	* Static function which takes a string and hashifies it into 
	* a single integer
	* @param str The string that requires hashing
	* @return Returns the hash value (integer) of the string
	*/
	static inline vhash_int Hashify(const char* str)
	{
		vhash_int hash = 2166136261;

		while (*str)
		{
			hash ^= *str++;
			hash *= 16777619;
		}

		return hash;
	}
};