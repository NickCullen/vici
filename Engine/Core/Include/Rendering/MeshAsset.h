#ifndef V_MESH_ASSET
#define V_MESH_ASSET

/* Forward Decl */
class ShaderAsset;

#include "Asset.h"

/**
* MeshAsset is responsible for loading the Vici
* specific .mesh files genereated from tools such as
* the objconverter.py script. It will generate all the 
* OpenGL vertex buffers and the indices that can be used
* to render a mesh
*/

class CORE_API MeshAsset : public Asset
{
	ASSET_REGISTER_DEF(MeshAsset)
private:
	BufferHandle _vertex_buffer;	/**< The integer representing the vertex buffer */
	BufferHandle _uv_buffer;		/**< The integer representing the vertex buffer */
	BufferHandle _normal_buffer;	/**< The integer representing the vertex buffer */
	BufferHandle _tangent_buffer; /**< The integer representing the vertex buffer */
	BufferHandle _binormal_buffer;/**< The integer representing the vertex buffer */
	BufferHandle* _index_buffers;	/**< The index buffers array */

	float* _vertex_array;	/**< The array of vertices */
	float* _uv_array;		/**< The array of uvs */
	float* _normal_array;	/**< The array of normals */
	float* _tangent_array;	/**< The array of tangents */
	float* _binormal_array;	/**< The array of binormals */

	int32 _vertex_count;	/**< Number of vertices in _vertex_array */
	int32 _uv_count;		/**< Number of vertices in _uv_array */
	int32 _normal_count;	/**< Number of vertices in _normal_array */
	int32 _tangent_count;   /**< Number of vertices in _tangent_array */
	int32 _binormal_count;	/**< Number of vertices in _binormal_array */

	uint32** _index_arrays;	/**< The array of index arrays describing faces */
	int32* _index_count;	/**< Number of indices in its relevant index array */

	int32 _num_arrays;	/**< Number of index arrays */

	char _file_path[BUFF_LEN]; /**< The full path to the mesh file */

public:
	/**
	* Default constructor
	*/
	MeshAsset();

	/**
	* Default destructor
	*/
	~MeshAsset();

	/**
	* Will set the mesh file name from xml node
	* @param node The xml node containing mesh data
	*/
	void Load(XmlNode& node);

	/**
	* Unloads the mesh asset
	*/
	void Unload();

	/**
	* Called so the mesh can set its attribues to the shader
	* @param shader The shader with the locations of inputs
	*/
	void SetArrays(ShaderAsset* shader);

	/**
	* Called to execute the draw elements functions. This is the Mesh
	* job because it knows the topology of the mesh
	*/
	void DrawElements(uint32 index);
};








#endif