#include "Shader.h"
#include "GL/glew.h"
#include <string>
#include "TextFile.h"


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

	//set all locations to -1
	_COMMON_SHADER_LOCATIONS(_GEN_DEFAULT_VAL)

	Loaded = false;
}


bool VShader::Load(const char* vertexShaderPath, const char* fragShaderPath)
{
	VHandle = glCreateShader(GL_VERTEX_SHADER);
	FHandle = glCreateShader(GL_FRAGMENT_SHADER);

	// store paths..
	strcpy(VPath, vertexShaderPath);
	strcpy(FPath, fragShaderPath);

	VTextFile vs = VTextFile(VPath);
	VTextFile fs = VTextFile(FPath);

	if (!vs.IsLoaded())
	{
		printf("\n\nERROR: file: %s not found -  ", VPath);
		return false;
	}
	if (!fs.IsLoaded())
	{
		printf("\n\nERROR: file: %s not found -  ", VPath);
		return false;
	}

	char *vv = NULL;
	char *ff = NULL;

	//flags to check to see if we need to manage deleteion of vv or ff
	bool delete_vv = false;
	bool delete_ff = false;

	//check if vertex shader requires common code
	char* vertexCommon = strstr((char*)vs, "#include common");
	if (vertexCommon != NULL)
	{
		//number of characters to copy before splitting code
		int32 pre_text_size = (int32)(vertexCommon - (char*)vs);

		//cycle until new line
		while (*vertexCommon != '\n')
			vertexCommon++;

		//++ 1 more to get rid of new line
		vertexCommon++;

		//allocate enough space in vv
		vv = new char[pre_text_size + strlen(CommonCode) + strlen(vertexCommon) + 1];
		
		//copy over a number of chars frm original string
		strncpy(vv, (char*)fs, pre_text_size);
		ff[pre_text_size] = '\0';
		strcat(vv, CommonCode);
		strcat(vv, vertexCommon);

		//set to true
		delete_vv = true;
	}
	else
	{
		vv = vs;
	}

	//check if frag shader requires common code
	char* fragCommon = strstr((char*)fs, "#include common");
	if (fragCommon != NULL)
	{
		//number of characters to copy before splitting code
		int32 pre_text_size = (int32)(fragCommon - (char*)fs);

		//cycle until new line
		while (*fragCommon != '\n')
			fragCommon++;

		//++ 1 more to get rid of new line
		fragCommon++;

		//allocate enough space in vv
		ff = new char[pre_text_size + strlen(CommonCode) + strlen(fragCommon) + 1];

		//copy over a number of chars frm original string
		strncpy(ff, (char*)fs, pre_text_size);
		ff[pre_text_size] = '\0';
		strcat(ff, CommonCode);
		strcat(ff, fragCommon);

		//set to true
		delete_ff = true;
	}
	else
	{
		ff = fs;
	}

	//set shader source
	glShaderSource(VHandle, 1, &vv, NULL);
	glShaderSource(FHandle, 1, &ff, NULL);

	//compile and check for errors
	glCompileShader(VHandle);
	DebugShader(VHandle, GL_COMPILE_STATUS);
	glCompileShader(FHandle);
	DebugShader(FHandle, GL_COMPILE_STATUS);

	//create program and attach shaders
	Program = glCreateProgram();
	glAttachShader(Program, VHandle);
	glAttachShader(Program, FHandle);

	//link the shaders to program and check for error
	glLinkProgram(Program);

	//print any errors
	DebugProgram(Program, GL_LINK_STATUS);

	//get the locations
	_COMMON_SHADER_LOCATIONS(_GEN_LOCATIONS)

	//set true
	Loaded = true;

	//free up if needed
	if (delete_vv) delete [] vv;
	if (delete_ff) delete [] ff;

	return true;
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
			printf("Error in shader %d - %s\n", Program, infoLog);
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
			printf("Error in program %d - %s\n", Program, infoLog);
			delete(infoLog);
		}
	}
}

SamplerHandle VShader::SamplerLocation(const char* id)
{
	return glGetUniformLocation(Program, id);
}

UniformHandle VShader::UniformLocation(const char* id)
{
	return glGetUniformLocation(Program, id);
}

UniformHandle VShader::AttributeLocation(const char* id)
{
	return glGetAttribLocation(Program, id);
}
void VShader::LoadSharedCode(const char* cwd)
{
	if (CommonCode == nullptr)
	{
		char buff[512];
		sprintf(buff, "%s%s", cwd, "/Assets/Common.shaders");

		VTextFile tf(buff);

		if (tf.IsLoaded())
		{
			CommonCode = new char[strlen(tf) + 1];
			strcpy(CommonCode, tf);
		}
	}
}

void VShader::UnloadSharedCode()
{
	if (CommonCode != NULL)
	{
		delete [] CommonCode;
	}
}