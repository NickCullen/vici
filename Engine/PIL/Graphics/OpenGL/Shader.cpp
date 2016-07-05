#include "PIL/Graphics/Shader.h"
#include "PIL/Collections/String.h"
#include "PIL/FileSystem/TextFile.h"
#include "PIL/Graphics/Renderer.h"
#include "PIL/FileSystem/FilePath.h"
#include "PIL/Graphics/OpenGL/Glew.h"
#include "PIL/Collections/Array.h"
#include "PIL/Graphics/VertexBuffer.h"
#include "GLTypeConverters.h"

// init statics
char* VShader::CommonCode = nullptr;
VShader* VShader::ActiveShader = nullptr;

// Non-public abi definitions
struct VShaderInputHandle
{
	GLint GLLocationHandle;
};

struct VShaderHandle
{
	GLint ProgramHandle;
	GLint VertexHandle;
	GLint GeomHandle;
	GLint FragHandle;

	VArray<VShaderInputHandle*> Unforms;
	VArray<VShaderInputHandle*> Attributes;		// Per vertex attributes

	VShaderHandle()
		:ProgramHandle(-1),
		VertexHandle(-1),
		GeomHandle(-1),
		FragHandle(-1) {}
};

// Converts enum to GL specific type
inline GLuint ShaderDebugFlagToGL(EShaderDebugFlag flag)
{
	switch (flag)
	{
		case SHADER_COMPILE_STATUS:		return GL_COMPILE_STATUS;
		case SHADER_LINK_STATUS:		return GL_LINK_STATUS;
		default:						return GL_COMPILE_STATUS;
	}
}

inline GLuint ShaderTypeToGL(EShaderType shaderType)
{
	switch (shaderType)
	{
		case SHADER_VERTEX:		return GL_VERTEX_SHADER;
		case SHADER_GEOMETRY:	return GL_GEOMETRY_SHADER;
		case SHADER_FRAGMENT:	return GL_FRAGMENT_SHADER;
		default:				return GL_VERTEX_SHADER;
	}
}

VShader::VShader()
	:ShaderHandle(nullptr),
	Loaded(false),
	ShaderPath(nullptr)
{
	//set all locations to -1
	_COMMON_SHADER_LOCATIONS(_GEN_DEFAULT_VAL)
}

VShader::~VShader()
{
	Unload();
}

void DebugShader(EShaderDebugFlag checkType, GLint shader, const char* identifier)
{
	//check for errors
	int noError;
	glGetShaderiv(shader, ShaderDebugFlagToGL(checkType), &noError);
	if (!noError)
	{
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen>1)
		{
			char* infoLog = new char[infoLen];
			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			printf("Error in shader %s (shader ID: %d) - %s\n", identifier, shader, infoLog);
			delete [] infoLog;
		}
	}
}


void DebugProgram(GLuint program, EShaderDebugFlag checkType)
{
	GLuint checkTypeGL = ShaderDebugFlagToGL(checkType);

	//check for errors
	int noError;
	glGetProgramiv(program, checkTypeGL, &noError);
	if (!noError)
	{
		GLint infoLen = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen>1)
		{
			char* infoLog = new char[infoLen];
			glGetProgramInfoLog(program, infoLen, NULL, infoLog);
			printf("Error in program %d - %s\n", program, infoLog);
			delete[] infoLog;
		}
	}
}

void VShader::Debug(EShaderDebugFlag checkType)
{
	DebugProgram(ShaderHandle->ProgramHandle, checkType);
}

void VShader::Unload()
{
	if (ShaderHandle->VertexHandle > 0)
		glDeleteShader(ShaderHandle->VertexHandle);
	if (ShaderHandle->FragHandle > 0)
		glDeleteShader(ShaderHandle->GeomHandle);
	if (ShaderHandle->FragHandle > 0)
		glDeleteShader(ShaderHandle->FragHandle);
	if (ShaderHandle->ProgramHandle > 0)
		glDeleteProgram(ShaderHandle->ProgramHandle);

	//set all locations to -1
	_COMMON_SHADER_LOCATIONS(_GEN_DEFAULT_VAL)

	if (ShaderPath)
		delete (ShaderPath);
	ShaderPath = nullptr;

	Loaded = false;
}


bool VShader::Load(const VFilePath& shaderPath)
{
	VTextFile vs = VTextFile((shaderPath+".vert"));
	VTextFile gs = VTextFile((shaderPath + ".geo"));
	VTextFile fs = VTextFile((shaderPath + ".frag"));
	
	// Create handles
	ShaderHandle = new VShaderHandle();
	int loadedCount = 0;
	if (vs.IsLoaded())
	{
		ShaderHandle->VertexHandle = glCreateShader(GL_VERTEX_SHADER);
		loadedCount++;
	}

	if (gs.IsLoaded())
	{
		ShaderHandle->GeomHandle = glCreateShader(GL_GEOMETRY_SHADER);
		loadedCount++;
	}

	if (fs.IsLoaded())
	{
		ShaderHandle->FragHandle = glCreateShader(GL_FRAGMENT_SHADER);
		loadedCount++;
	}

	// If nothing got loaded return false!
	if (loadedCount == 0)
	{
		printf("[Shader] ERROR! : Could not load shader at %s\n", shaderPath.GetString());
		delete(ShaderHandle);
		return false;
	}

	// store note to path for reloading..
	ShaderPath = new VFilePath(shaderPath);

	char *vv = nullptr;
	char *gg = nullptr;
	char *ff = nullptr;

	//flags to check to see if we need to manage deleteion of vv or ff
	bool delete_vv = false;
	bool delete_gg = false;
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

	//check if geom shader requires common code
	char* geoCommon = strstr((char*)vs, "#include common");
	if (geoCommon != NULL)
	{
		//number of characters to copy before splitting code
		int32 pre_text_size = (int32)(geoCommon - (char*)gs);

		//cycle until new line
		while (*geoCommon != '\n')
			geoCommon++;

		//++ 1 more to get rid of new line
		geoCommon++;

		//allocate enough space in vv
		gg = new char[pre_text_size + strlen(CommonCode) + strlen(geoCommon) + 1];

		//copy over a number of chars frm original string
		strncpy(gg, (char*)gs, pre_text_size);
		gg[pre_text_size] = '\0';
		strcat(gg, CommonCode);
		strcat(gg, vertexCommon);

		//set to true
		delete_gg = true;
	}
	else
	{
		gg = gs;
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

	// Set the source code for each shader & compile
	if (ShaderHandle->VertexHandle > 0)
	{
		glShaderSource(ShaderHandle->VertexHandle, 1, &vv, NULL);
		glCompileShader(ShaderHandle->VertexHandle);
		DebugShader(SHADER_COMPILE_STATUS, ShaderHandle->VertexHandle, (shaderPath + ".vert").GetString());
	}

	if (ShaderHandle->GeomHandle > 0)
	{
		glShaderSource(ShaderHandle->GeomHandle, 1, &gg, NULL);
		glCompileShader(ShaderHandle->GeomHandle);
		DebugShader(SHADER_COMPILE_STATUS, ShaderHandle->GeomHandle, (shaderPath + ".geo").GetString());
	}

	if (ShaderHandle->FragHandle > 0)
	{
		glShaderSource(ShaderHandle->FragHandle, 1, &ff, NULL);
		glCompileShader(ShaderHandle->FragHandle);
		DebugShader(SHADER_COMPILE_STATUS, ShaderHandle->FragHandle, (shaderPath + ".frag").GetString());
	}

	// Create program
	ShaderHandle->ProgramHandle = glCreateProgram();

	// Link shader programs
	if (ShaderHandle->VertexHandle > 0)
		glAttachShader(ShaderHandle->ProgramHandle, ShaderHandle->VertexHandle);

	if (ShaderHandle->GeomHandle > 0)
		glAttachShader(ShaderHandle->ProgramHandle, ShaderHandle->GeomHandle);

	if (ShaderHandle->FragHandle > 0)
		glAttachShader(ShaderHandle->ProgramHandle, ShaderHandle->FragHandle);

	// Execute the link process
	glLinkProgram(ShaderHandle->ProgramHandle);

	//print any errors
	Debug(SHADER_LINK_STATUS);

	//get the locations
	_COMMON_SHADER_LOCATIONS(_GEN_LOCATIONS)

	//set true
	Loaded = true;

	//free up if needed
	if (delete_vv) delete[] vv;
	if (delete_gg) delete[] gg;
	if (delete_ff) delete[] ff;

	return true;
}

void VShader::Use()
{
	if (ShaderHandle->ProgramHandle > 0)
	{
		ActiveShader = this;
		glUseProgram(ShaderHandle->ProgramHandle);
	}
}


VShaderInputHandle* VShader::SamplerLocation(const char* id)
{
	return UniformLocation(id);	// Basically a uniform in OpenGL...
}

VShaderInputHandle* VShader::UniformLocation(const char* id)
{
	// First ensure it actually exists
	GLint loc = glGetUniformLocation(ShaderHandle->ProgramHandle, id);
	if (loc == -1)
		return nullptr;

	// Create uniform handle and retrieve it
	for each (VShaderInputHandle* handle in ShaderHandle->Unforms)
	{
		if (handle->GLLocationHandle == loc)
			return handle;
	}

	// If we got here this means we need to add it to the Uniforms list
	VShaderInputHandle* newHandle = new VShaderInputHandle();
	newHandle->GLLocationHandle = loc;

	ShaderHandle->Unforms.push_back(newHandle);

	return newHandle;
}

VShaderInputHandle* VShader::AttributeLocation(const char* id)
{
	GLint loc = glGetAttribLocation(ShaderHandle->ProgramHandle, id);
	if (loc == -1)
		return nullptr;

	// Create uniform handle and retrieve it
	for each (VShaderInputHandle* handle in ShaderHandle->Attributes)
	{
		if (handle->GLLocationHandle == loc)
			return handle;
	}

	// If we got here this means we need to add it to the Uniforms list
	VShaderInputHandle* newHandle = new VShaderInputHandle();
	newHandle->GLLocationHandle = loc;

	ShaderHandle->Attributes.push_back(newHandle);

	return newHandle;
}

void VShader::BindFragDataLocation(const char* id, uint32 location)
{
	glBindFragDataLocation(ShaderHandle->ProgramHandle, location, id);
}

void VShader::LoadSharedCode(const char* cwd)
{
	if (CommonCode == nullptr)
	{
		VString path = cwd + VString("/Assets/Common.shaders");

		VTextFile tf(path);

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

void VShader::EnableVertexArray(VShaderInputHandle* attributeHandle)
{
	glEnableVertexAttribArray(attributeHandle->GLLocationHandle);
}

void VShader::VertexAttribPointer(VShaderInputHandle* attributeHandle, const VVertexElement* vertexElement, int32 vertexSize)
{
	glVertexAttribPointer(attributeHandle->GLLocationHandle,
		vertexElement->Info.NumOfComponents,
		GLTypeConverter::ElementTypeToGL(vertexElement->Info.Type),
		vertexElement->Info.Normalize ? GL_TRUE : GL_FALSE,
		vertexSize,
		(void*)vertexElement->Offset);
}


#pragma region - OPENGL Specific Functions -

#ifdef VICI_OPENGL

uint32 VShader::ShaderInputToGL(VShaderInputHandle* inputHandle)
{
	return inputHandle->GLLocationHandle;
}

#endif

#pragma endregion