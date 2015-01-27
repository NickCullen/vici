#include "Shader.h"
#include "Vici.h"
#include <string>
#include "TextFile.h"

Shader::Shader()
{
	_v = 0;
	_f = 0;

	_program = 0;

	_mvp_loc = -1;
	_normal_loc = -1;

	_is_loaded = false;
}

Shader::~Shader()
{
	Clean();
}


void Shader::Clean()
{
	if (_v)
		glDeleteShader(_v);
	if (_f)
		glDeleteShader(_f);
	if (_program)
		glDeleteProgram(_program);

	_is_loaded = false;
}
void Shader::Create(char *pVertexShader_path, char *pFragmentShader_Path)
{
	_v = glCreateShader(GL_VERTEX_SHADER);
	_f = glCreateShader(GL_FRAGMENT_SHADER);


	// store vertex path..
	sprintf(_v_path, "%s/%s", _vici->GetCwd(), pVertexShader_path);
	strcpy(_v_path, Platform_Pathify(_v_path));

	// store shader path..
	sprintf(_f_path, "%s/%s", _vici->GetCwd(), pFragmentShader_Path);
	strcpy(_f_path, Platform_Pathify(_f_path));

	TextFile vs = TextFile(_v_path);
	TextFile fs = TextFile(_f_path);

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


	const char *vv = vs;
	const char *ff = fs;

	glShaderSource(_v, 1, &vv, NULL);
	glShaderSource(_f, 1, &ff, NULL);


	//compile and check for errors
	glCompileShader(_v);
	DebugShader(_v, GL_COMPILE_STATUS);
	glCompileShader(_f);
	DebugShader(_f, GL_COMPILE_STATUS);

	_program = glCreateProgram();
	glAttachShader(_program, _v);
	glAttachShader(_program, _f);

	//link the shaders to program and check for error
	glLinkProgram(_program);

	DebugProgram(_program, GL_LINK_STATUS);

	_mvp_loc = glGetUniformLocation(_program, "uMVP");
	_normal_loc = glGetUniformLocation(_program, "uNormalMatrix");
	_vertex_location = glGetAttribLocation(_program, "aVertex");
	_normal_loc = glGetAttribLocation(_program, "aNormal");
	_uv_location = glGetAttribLocation(_program, "aUV");

	_is_loaded = true;
}


void Shader::DebugShader(GLuint shader, GLenum checkType)
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


void Shader::DebugProgram(GLuint program, GLenum checkType)
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