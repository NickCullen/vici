#ifndef V_VHASH
#define V_VHASH

//the typedef for a hash
typedef unsigned int vhash_int; 

class VHash
{
private:
	vhash_int _hash;
public:
	~VHash();

	VHash();
	VHash(const VHash& other);
	VHash(const char* str);
	VHash(char* str);

	//condition ==
	bool operator==(vhash_int other);
	bool operator==(const VHash& other);
	bool operator==(const char* other);
	bool operator==(char* other);

	//condition !=
	bool operator!=(vhash_int other);
	bool operator!=(const VHash& other);
	bool operator!=(const char* other);
	bool operator!=(char* other);

	//copying
	VHash operator=(vhash_int eq);
	VHash operator=(const char* eq);
	VHash operator=(char* eq);


	//getters
	inline vhash_int Value()
	{
		return _hash;
	}

	//the hash function
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

#endif
