#include "ShaderAsset.h"
#include "Platform.h"
#include <string>
#include "TextFile.h"

// init statics
char* ShaderAsset::_common_code = NULL;

ShaderAsset::ShaderAsset() : Asset()
{
	_v = 0;
	_f = 0;

	_program = 0;

	_is_loaded = false;

	//set all locations to -1
	_COMMON_SHADER_LOCATIONS(_GEN_DEFAULT_VAL)

}

ShaderAsset::~ShaderAsset()
{

}


void ShaderAsset::Unload()
{
	if (_v)
		glDeleteShader(_v);
	if (_f)
		glDeleteShader(_f);
	if (_program)
		glDeleteProgram(_program);

	_is_loaded = false;
}

void ShaderAsset::Load(XmlNode& node)
{
	_v = glCreateShader(GL_VERTEX_SHADER);
	_f = glCreateShader(GL_FRAGMENT_SHADER);

	// store vertex path..
	sprintf(_v_path, "%s/%s", _Platform->GetCwd(), node.GetString("vert"));
	strcpy(_v_path, _Platform->Pathify(_v_path));

	// store shader path..
	sprintf(_f_path, "%s/%s", _Platform->GetCwd(), node.GetString("frag"));
	strcpy(_f_path, _Platform->Pathify(_f_path));

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


void ShaderAsset::DebugShader(GLuint shader, GLenum checkType)
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


void ShaderAsset::DebugProgram(GLuint program, GLenum checkType)
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

GLint ShaderAsset::SamplerLocation(const char* id)
{
	return glGetUniformLocation(_program, id); 
}

GLint ShaderAsset::UniformLocation(const char* id)
{
	return glGetUniformLocation(_program, id);
}

void ShaderAsset::LoadSharedCode(std::string cwd)
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

void ShaderAsset::UnloadSharedCode()
{
	if (_common_code != NULL)
	{
		delete(_common_code);
	}
}