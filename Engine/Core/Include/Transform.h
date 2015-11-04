#ifndef V_TRANSFORM
#define V_TRANSFORM

/*Forward decl*/

#include "glm.h"
#include "Xml.h"

/**
* Transform containing information on moving and representing 
* the object in the world
*/

class Transform
{
private:
	glm::vec3 _pos;	/**< Position of object */
	glm::vec3 _scale;	/**< Scale of object */
	glm::vec3 _rotation;	/**< rotation of object */

	glm::mat4x4 _model;	/**< Model Matrix */

	glm::mat4x4 _rotation_matrix;	/**< Rotation matrix */

	bool _update_model_matrix;	/**< Flag to set to true when model matrix needs updating - this gets set to true when a transformation has been applied to any pos, rot or scale */
public:
	/**
	* Default constructor
	*/
	Transform();

	/**
	* Default destructor
	*/
	~Transform();

	/**
	* Loads the transform from the given xml node
	* @param node The XmlNode containing the data
	*/
	void Init(XmlNode& node);

	/**
	* Translates the position
	* @param offset The ammount to be added to the _pos
	*/
	void Translate(glm::vec3 offset);

	/**
	* Translate the position
	* @param x The ammount to be added to the _pos.x
	* @param y The ammount to be added to the _pos.y
	* @param z The ammount to be added to the _pos.z
	*/
	void Translate(float x, float y, float z);

	/**
	* Sets all components of _scale(.xyz) to the given value
	* @param scale Sets _scale(.xyz) = scale
	*/
	void Scale(float scale);

	/**
	* Sets the individual components of _scale to the given values
	* @param scale_x _scale.x = scale_x
	* @param scale_y _scale.y = scale_y
	* @param scale_z _scale.z = scale_z
	*/
	void Scale(float scale_x, float scale_y, float scale_z);

	/**
	* Sets the scale of the object to the given vec3 scale
	* @param scale Sets _scale to glm::vec3 scale
	*/
	void Scale(glm::vec3 scale);

	/**
	* Rotate the object by the angle (degrees) on the given axis
	* @param angle The angle in degrees
	* @param axis The axis to rotate on
	*/
	void Rotate(float angle, glm::vec3 axis);

	/**
	* Rotate the object by the angle (degrees) on the given axis
	* @param angle The angle in degrees
	* @param ax_x Value of X axis
	* @param ax_y Value of Y axis
	* @param ax_z Value of Z axis
	*/
	void Rotate(float angle, float ax_x, float ax_y, float ax_z);

	/**
	* Returns the model matrix - will recompute model matrix
	* if _update_model_matrix is set to true
	* @return A 4x4 matrix containing the values for this transforms model matrix
	*/
	glm::mat4 GetModelMatrix();

	/**
	* Returns the position of this object
	* @return vec3 containing the position of this object
	*/
	inline glm::vec3 GetPosition()
	{
		return _pos;
	}

	/**
	* Returns the rotation of this object
	* @return vec3 containing the Euler angles of this transform
	*/
	inline glm::vec3 GetRotation()
	{
		return _rotation;
	}

	/**
	* Returns the scale of this object
	* @return vec3 containing the scale of this object
	*/
	inline glm::vec3 GetScale()
	{
		return _scale;
	}

	/**
	* Returns the forward direction of this object. It rotates
	* the initial default forward vector (0,0,-1) by the rotation
	* matrix - Note that this may recompute the model + rotation matrix 
	* if _update_model_matrix is set to true!
	* @return vec4 containing the way this object is facing
	*/
	inline glm::vec4 ForwardDirection()
	{
		static glm::vec4 initial_direction(0.0f,0.0f,-1.0f,1.0f);
		UpdateMatrix();
		return initial_direction * _rotation_matrix;
	}

	/**
	* Call this function to automatically recompute
	* the model and rotation matrices. It will only 
	* carry out the execution if _update_model_matrix
	* is set to true
	*/
	void UpdateMatrix();
};

#endif