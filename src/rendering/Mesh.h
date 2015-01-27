#ifndef V_MESH
#define V_MESH

/* Forward Decl */
class Shader;

#include "IComponent.h"

/** 
* Component which holds the buffers and vertex arrays
* Used to describe a mesh
*/

class Mesh : public IComponent
{
private:
	uint32 _vertex_buffer;	/**< The integer representing the vertex buffer */
	uint32 _uv_buffer;		/**< The integer representing the vertex buffer */
	uint32 _normal_buffer;	/**< The integer representing the vertex buffer */
	uint32 _index_buffer;		/**< The index buffer array */

	float* _vertex_array;	/**< The array of vertices */
	float* _uv_array;		/**< The array of uvs */
	float* _normal_array;	/**< The array of normals */

	int32 _vertex_count;	/**< Number of vertices in _vertex_array */
	int32 _uv_count;		/**< Number of vertices in _uv_array */
	int32 _normal_count;	/**< Number of vertices in _normal_array */

	uint32* _index_array;	/**< The index array describing faces */
	int32 _index_count;		/**< Number of indices in index array */

	uint32 vao;

	char _file_path[MAX_PATH]; /**< The full path to the mesh file */

protected:

public:
	/**
	* Default Mesh Constructor will init all
	* member vars to NULL 
	*/
	Mesh();

	/**
	* Default destructor
	*/
	~Mesh();

	/**
	* Will set the mesh file name from xml node
	* @param node The xml node containing component data
	*/
	virtual void Init(rapidxml::xml_node<char>* node);

	/**
	* Setting the file name will load the file
	* and create needed buffers
	* Note that this will soon change to use assets instead of direct loading
	* @param file The path to the file name including extension
	*/
	void SetMeshFile(char* file);

	/** 
	* Called so the mesh can set its attribues to the shader
	* @param shader The shader with the locations of inputs
	*/
	void SetArrays(Shader* shader);

	/**
	* Called to execute the draw elements functions. This is the Mesh
	* job because it knows the topology of the mesh*
	*/
	void DrawElements();

	/** 
	* Generates the buffers for the arrays
	* @param shader The shader whos locations we use
	*/
	void CreateBuffers(Shader* shader);

	static DerivedRegister<Mesh> reg; /**< Used to register Component */
};

#endif