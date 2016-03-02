#include "Shader.h"
#include "GL/glew.h"
#include <string>

// init statics
char* VShader::CommonCode = nullptr;

VShader::VShader()
	:VHandle(-1),
	FHandle(-1),
	Program(-1),
	Loaded(false)
{
	//set all locations to -1
	_COMMON_SHADER_LOCATIONS(_GEN_DEFAULT_VAL)
}

VShader::~VShader()
{
	Unload();
}


void VShader::Unload()
{
	if (VHandle > 0)
		glDeleteShader(VHandle);
	if (FHandle > 0)
		glDeleteShader(FHandle);
	if (Program > 0)
		glDeleteProgram(Program);

	Loaded = false;
}


bool VShader::Load(const char* vertexShaderPath, const char* fragShaderPath)
{
	VHandle = glCreateShader(GL_VERTEX_SHADER);
	FHandle = glCreateShader(GL_FRAGMENT_SHADER);

	// store paths..
	strcpy(VPath, vertexShaderPath);
	strcpy(FPath, fragShaderPath);

	TextFile vs = TextFile(VPath);
	TextFile fs = TextFile(FPath);

	if (!vs.IsLoaded())
	{
		printf("\n\nERROR: file: %s not found -  ", _v_path);
		return;
	}
	if (!fs.IsLoaded())
	{
		printf("\n\nERROR: file: %s not found -  ", _f_path);
		return;
	}

	char *vv = NULL;
	char *ff = NULL;

	//flags to check to see if we need to manage deleteion of vv or ff
	bool delete_vv = false;
	bool delete_ff = false;

	//check if vertex shader requires common code
	char* vertex_common = strstr((char*)vs, "#include common");
	if (vertex_common != NULL)
	{
		//number of characters to copy before splitting code
		int32 pre_text_size = (int32)(vertex_common - (char*)vs);

		//cycle until new line
		while (*vertex_common != '\n')
			vertex_common++;

		//++ 1 more to get rid of new line
		vertex_common++;

		//allocate enough space in vv
		vv = new char[pre_text_size + strlen(_common_code) + strlen(vertex_common) + 1];
		
		//copy over a number of chars frm original string
		strncpy(vv, (char*)fs, pre_text_size);
		ff[pre_text_size] = '\0';
		strcat(vv, _common_code);
		strcat(vv, vertex_common);

		//set to true
		delete_vv = true;
	}
	else
	{
		vv = vs;
	}

	//check if frag shader requires common code
	char* frag_common = strstr((char*)fs, "#include common");
	if (frag_common != NULL)
	{
		//number of characters to copy before splitting code
		int32 pre_text_size = (int32)(frag_common - (char*)fs);

		//cycle until new line
		while (*frag_common != '\n')
			frag_common++;

		//++ 1 more to get rid of new line
		frag_common++;

		//allocate enough space in vv
		ff = new char[pre_text_size + strlen(_common_code) + strlen(frag_common) + 1];

		//copy over a number of chars frm original string
		strncpy(ff, (char*)fs, pre_text_size);
		ff[pre_text_size] = '\0';
		strcat(ff, _common_code);
		strcat(ff, frag_common);

		//set to true
		delete_ff = true;
	}
	else
	{
		ff = fs;
	}

	//set shader source
	glShaderSource(_v, 1, &vv, NULL);
	glShaderSource(_f, 1, &ff, NULL);

	//compile and check for errors
	glCompileShader(_v);
	DebugShader(_v, GL_COMPILE_STATUS);
	glCompileShader(_f);
	DebugShader(_f, GL_COMPILE_STATUS);

	//create program and attach shaders
	_program = glCreateProgram();
	glAttachShader(_program, _v);
	glAttachShader(_program, _f);

	//link the shaders to program and check for error
	glLinkProgram(_program);

	//print any errors
	DebugProgram(_program, GL_LINK_STATUS);

	//get the locations
	_COMMON_SHADER_LOCATIONS(_GEN_LOCATIONS)

	//set true
	_is_loaded = true;

	//free up if needed
	if (delete_vv) delete(vv);
	if (delete_ff) delete(ff);
}


void VShader::DebugShader(ShaderHandle shader, ShaderDebugFlags checkType)
{
	//check for errors
	int noError;
	glGetShaderiv(shader, checkType, &noError);
	if (!noError)
	{
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen>1)
		{
			char* infoLog = new char[infoLen];
			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			printf("Error in shader %d - %s\n", _program, infoLog);
			delete(infoLog);
		}
	}
}


void VShader::DebugProgram(ShaderHandle program, ShaderDebugFlags checkType)
{
	//check for errors
	int noError;
	glGetProgramiv(program, checkType, &noError);
	if (!noError)
	{
		GLint infoLen = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen>1)
		{
			char* infoLog = new char[infoLen];
			glGetProgramInfoLog(program, infoLen, NULL, infoLog);
			printf("Error in program %d - %s\n", _program, infoLog);
			delete(infoLog);
		}
	}
}

SamplerHandle VShader::SamplerLocation(const char* id)
{
	return glGetUniformLocation(_program, id); 
}

UniformHandle VShader::UniformLocation(const char* id)
{
	return glGetUniformLocation(_program, id);
}

void VShader::LoadSharedCode(std::string cwd)
{
	if (_common_code == NULL)
	{
		cwd += "/Assets/Common.shaders";
		char buff[256];
		strcpy(buff, _Platform->Pathify(cwd.c_str()));

		TextFile tf(buff);

		if (tf.IsLoaded())
		{
			_common_code = new char[strlen(tf) + 1];
			strcpy(_common_code, tf);
		}
	}
}

void VShader::UnloadSharedCode()
{
	if (_common_code != NULL)
	{
		delete(_common_code);
	}
}