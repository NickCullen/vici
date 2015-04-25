#ifndef V_SQUIRREL
#define V_SQUIRREL

#include "Singleton.h"
#include "squirrel.h"


class Squirrel : public Singleton<Squirrel>
{
	friend class SQScriptAsset;
private:
	HSQUIRRELVM _v;	/**< The squirrel environment */
	
	/**
	* Called by squirrel vm to compile file in buffer
	*/
	static SQInteger FeedASCII(SQUserPointer file);

	/**
	* Called internally by SQScriptAsset to compile a file
	* @param filename Pointer to the filename
	*/
	bool CompileFile(const char *filename);

	/**
	* Logs the error of given scripts
	*/
	static void ScriptError(HSQUIRRELVM, const SQChar * desc, const SQChar * source, SQInteger line, SQInteger column);
public:
	
	/**
	* Default constructor
	*/
	Squirrel();

	/**
	* Default destructor
	*/
	virtual ~Squirrel();

	/**
	* Called to inialize squirrel
	*/
	void Init();

	/**
	* Returns the squirel environment
	* @return Structure containing the squirel environment
	*/
	inline HSQUIRRELVM GetSquirrelVM(){ return _v; }

};

#endif