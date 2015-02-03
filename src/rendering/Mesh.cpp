#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh()
{
	//Important to set the hash if for this component
	_hash = "Mesh";

	//default all to NULL
	_vertex_buffer = _uv_buffer = _normal_buffer = _index_buffer = NULL;
	_vertex_array = _uv_array = _normal_array = NULL;
	_vertex_count = _uv_count = _normal_count = 0;
	_index_array = NULL;
}
Mesh::~Mesh()
{
	//free memory
	if (_vertex_array != NULL) delete(_vertex_array);
	if (_uv_array != NULL) delete(_uv_array);
	if (_normal_array != NULL) delete(_normal_array);
	if (_index_array != NULL) delete(_index_array);
}

void Mesh::Init(XmlNode& node)
{
	//call parent init
	IComponent::Init(node);

	//get the mesh file
	char* file = node.GetChild("mesh").ValueString();
	
	//set mesh file (note this will trigger loading)
	SetMeshFile(file);
}



void Mesh::SetMeshFile(char* file)
{
	if (file == NULL) return;

	//set the full path to the file
	sprintf(_file_path, "%s/%s", _vici->GetCwd(), file);
	//make the path sensible for platform
	strcpy(_file_path, Platform_Pathify(_file_path));

	//open file
	FILE* f = fopen(_file_path, "rb");
	if (f)
	{
		//read the number of vertices
		fread(&_vertex_count, sizeof(int32), 1, f);

		//if not 0 copy them of
		if (_vertex_count != 0)
		{
			//allocate
			_vertex_array = new float[_vertex_count * 3];
			//cpy
			fread(_vertex_array, _vertex_count * sizeof(float) * 3, 1, f);

			//generate vertex buffer
			glGenBuffers(1, &_vertex_buffer);

			// The following commands will talk about our 'vertexbuffer' buffer
			glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);

			// Give our vertices to OpenGL.
			glBufferData(GL_ARRAY_BUFFER, _vertex_count * sizeof(float) * 3, _vertex_array, GL_STATIC_DRAW);
		}

		//read the number of uvs
		fread(&_uv_count, sizeof(int32), 1, f);
		//if not 0 copy them of
		if (_uv_count != 0)
		{
			//allocate
			_uv_array = new float[_uv_count * 2];
			//cpy
			fread(_uv_array, _uv_count * sizeof(float) * 2, 1, f);

			//generate vertex buffer
			glGenBuffers(1, &_uv_buffer);

			// The following commands will talk about our 'vertexbuffer' buffer
			glBindBuffer(GL_ARRAY_BUFFER, _uv_buffer);

			// Give our vertices to OpenGL.
			glBufferData(GL_ARRAY_BUFFER, _uv_count * sizeof(float)* 2, _uv_array, GL_STATIC_DRAW);
		}

		//read the number of norms
		fread(&_normal_count, sizeof(int32), 1, f);
		//if not 0 copy them of
		if (_normal_count != 0)
		{
			//allocate
			_normal_array = new float[_normal_count * 3];
			//cpy
			fread(_normal_array, _normal_count * sizeof(float)* 3, 1, f);

			//generate vertex buffer
			glGenBuffers(1, &_normal_buffer);

			// The following commands will talk about our 'vertexbuffer' buffer
			glBindBuffer(GL_ARRAY_BUFFER, _normal_buffer);

			// Give our vertices to OpenGL.
			glBufferData(GL_ARRAY_BUFFER, _normal_count * sizeof(float)* 3, _normal_array, GL_STATIC_DRAW);
		}

		//read the number of indices
		fread(&_index_count, sizeof(int32), 1, f);
		//if not 0 copy them of
		if (_index_count != 0)
		{
			//allocate
			_index_array = new uint32[_index_count];
			//cpy
			fread(_index_array, _index_count * sizeof(uint32), 1, f);

			//generate vertex buffer
			glGenBuffers(1, &_index_buffer);

			// The following commands will talk about our index buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);

			// Give our vertices to OpenGL.
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, _index_count * sizeof(uint32), _index_array, GL_STATIC_DRAW);
		}

		//close file
		fclose(f);
	}
}


void Mesh::SetArrays(Shader* shader)
{
	//Vertex Array
	if (_vertex_count > 0)
	{
		glEnableVertexAttribArray(shader->VertexLocation());
		glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
		glVertexAttribPointer(shader->VertexLocation(), 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
	
	//normal array
	if (_normal_count > 0)
	{
		glEnableVertexAttribArray(shader->NormalLocation());
		glBindBuffer(GL_ARRAY_BUFFER, _normal_buffer);
		glVertexAttribPointer(shader->NormalLocation(), 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	//uv array
	if (_normal_count > 0)
	{
		glEnableVertexAttribArray(shader->UVLocation());
		glBindBuffer(GL_ARRAY_BUFFER, _uv_buffer);
		glVertexAttribPointer(shader->UVLocation(), 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
}


void Mesh::DrawElements()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);
	glDrawElements(GL_TRIANGLES, _index_count, GL_UNSIGNED_INT, (void*)0);

}

