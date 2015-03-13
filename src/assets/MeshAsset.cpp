#include "MeshAsset.h"
#include "ShaderAsset.h"
#include "Vici.h"
#include "Platform.h"

MeshAsset::MeshAsset() : Asset()
{
	//default all to NULL
	//_vertex_buffer = _uv_buffer = _normal_buffer = NULL;
	_vertex_array = _uv_array = _normal_array = NULL;
	_vertex_count = _uv_count = _normal_count = 0;
	_num_arrays = 0;
}

MeshAsset::~MeshAsset()
{
	//free memory
	if (_vertex_array != NULL) delete(_vertex_array);
	if (_uv_array != NULL) delete(_uv_array);
	if (_normal_array != NULL) delete(_normal_array);

	for (int i = 0; i < _num_arrays; i++)
	{
		delete(_index_arrays[i]);
	}
	delete(_index_arrays);
}

void MeshAsset::Unload()
{

}
void MeshAsset::Load(XmlNode& node)
{
	//get the mesh file
	char* file = node.GetString("path");

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
			fread(_vertex_array, _vertex_count * sizeof(float)* 3, 1, f);

			//generate vertex buffer
			glGenBuffers(1, &_vertex_buffer);

			// The following commands will talk about our 'vertexbuffer' buffer
			glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);

			// Give our vertices to OpenGL.
			glBufferData(GL_ARRAY_BUFFER, _vertex_count * sizeof(float)* 3, _vertex_array, GL_STATIC_DRAW);
		}

		//read the number of uvs
		fread(&_uv_count, sizeof(int32), 1, f);
		//if not 0 copy them of
		if (_uv_count != 0)
		{
			//allocate
			_uv_array = new float[_uv_count * 2];
			//cpy
			fread(_uv_array, _uv_count * sizeof(float)* 2, 1, f);

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

		//read the number of norms
		fread(&_tangent_count, sizeof(int32), 1, f);
		//if not 0 copy them of
		if (_tangent_count != 0)
		{
			//allocate
			_tangent_array = new float[_tangent_count * 3];
			//cpy
			fread(_tangent_array, _tangent_count * sizeof(float) * 3, 1, f);

			//generate vertex buffer
			glGenBuffers(1, &_tangent_buffer);

			// The following commands will talk about our 'vertexbuffer' buffer
			glBindBuffer(GL_ARRAY_BUFFER, _tangent_buffer);

			// Give our vertices to OpenGL.
			glBufferData(GL_ARRAY_BUFFER, _tangent_count * sizeof(float) * 3, _tangent_array, GL_STATIC_DRAW);
		}

		//read the number of norms
		fread(&_binormal_count, sizeof(int32), 1, f);
		//if not 0 copy them of
		if (_binormal_count != 0)
		{
			//allocate
			_binormal_array = new float[_binormal_count * 3];
			//cpy
			fread(_binormal_array, _binormal_count * sizeof(float) * 3, 1, f);

			//generate vertex buffer
			glGenBuffers(1, &_binormal_buffer);

			// The following commands will talk about our 'vertexbuffer' buffer
			glBindBuffer(GL_ARRAY_BUFFER, _binormal_buffer);

			// Give our vertices to OpenGL.
			glBufferData(GL_ARRAY_BUFFER, _binormal_count * sizeof(float) * 3, _binormal_array, GL_STATIC_DRAW);
		}

		//read how many index arrays this mesh holds
		fread(&_num_arrays, sizeof(int32), 1, f);

		//allocate memory to size counters
		_index_count = new int32[_num_arrays];
		_index_arrays = new uint32*[_num_arrays];
		_index_buffers = new uint32[_num_arrays];

		//generate the buffers
		glGenBuffers(_num_arrays, _index_buffers);

		//generate the index arrays
		for (int32 i = 0; i < _num_arrays; i++)
		{
			//read the number of indices
			fread(&_index_count[i], sizeof(int32), 1, f);

			//allocate
			_index_arrays[i] = new uint32[_index_count[i]];

			//cpy
			fread(_index_arrays[i], _index_count[i] * sizeof(uint32), 1, f);

			// The following commands will talk about our index buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffers[i]);

			// Give our vertices to OpenGL.
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, _index_count[i] * sizeof(uint32), _index_arrays[i], GL_STATIC_DRAW);
		}

		//close file
		fclose(f);
	}
}

void MeshAsset::SetArrays(ShaderAsset* shader)
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

	//tangent array
	if (_tangent_count > 0)
	{
		glEnableVertexAttribArray(shader->TangentLocation());
		glBindBuffer(GL_ARRAY_BUFFER, _tangent_buffer);
		glVertexAttribPointer(shader->TangentLocation(), 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}
	//binormal array
	if (_normal_count > 0)
	{
		glEnableVertexAttribArray(shader->BinormalLocation());
		glBindBuffer(GL_ARRAY_BUFFER, _binormal_buffer);
		glVertexAttribPointer(shader->BinormalLocation(), 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	//uv array
	if (_normal_count > 0)
	{
		glEnableVertexAttribArray(shader->UVLocation());
		glBindBuffer(GL_ARRAY_BUFFER, _uv_buffer);
		glVertexAttribPointer(shader->UVLocation(), 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}


}


void MeshAsset::DrawElements(int32 index)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffers[index]);
	glDrawElements(GL_TRIANGLES, _index_count[index], GL_UNSIGNED_INT, (void*)0);

}

