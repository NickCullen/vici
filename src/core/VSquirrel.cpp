#include "VSquirrel.h"
#include <stdio.h>
#include "Vici.h"

Squirrel::Squirrel() : Singleton<Squirrel>(this)
{

	//create the squirrel environment
	_v = sq_open(1024);
}

Squirrel::~Squirrel()
{
	//close env
	sq_close(_v);
}

void Squirrel::Init()
{
	sq_setcompilererrorhandler(_v, ScriptError);
}

SQInteger Squirrel::FeedASCII(SQUserPointer file)
{
	int ret;
	char c;
	if ((ret = fread(&c, sizeof(c), 1, (FILE *)file)>0))
		return c;
	return 0;
}

bool Squirrel::CompileFile(const char *filename)
{
	FILE *f = fopen(filename, "rb");
	if (f)
	{
		sq_compile(_v, FeedASCII, f, filename, 1);
		fclose(f);
		return true;
	}
	return false;
}
void Squirrel::ScriptError(HSQUIRRELVM, const SQChar * desc, const SQChar * source, SQInteger line, SQInteger column)
{
	_Platform->LogString("Script Error!\n\t[Source]: %s\n\t[Description]: %s\n\t[Line]: %d\t[Column]: %d\n", source, desc, line, column);
}