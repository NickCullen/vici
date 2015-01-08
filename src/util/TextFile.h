#ifndef V_TEXTFILE
#define V_TEXTFILE

class TextFile
{
public:
	char* _text;

	TextFile(const char* path);
	~TextFile();

	//converstions to char* and const char*
	operator char*()
	{
		return _text;
	}

	operator const char*()
	{
		return (const char*)_text;
	}

	//returns true if loaded
	bool IsLoaded();
};


#endif