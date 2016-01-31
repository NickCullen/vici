#ifndef V_TRANSFORM
#define V_TRANSFORM

/*Forward decl*/

#include "PlatformDefinitions.h"
#include "CoreAPI.h"
#include "Serialization.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

/**
* Transform containing information on moving and representing 
* the object in the world
*/

class CORE_API Transform
{
private:
	Vector3f Pos;	/**< Position of object */
	Vector3f Scale;	/**< Scale of object */
	Vector3f Rotation;	/**< rotation of object */

	Matrix4f Model;	/**< Model Matrix */

	Matrix4f RotationMatrix;	/**< Rotation matrix */

	bool bUpdateModelMatrix;	/**< Flag to set to true when model matrix needs updating - this gets set to true when a transformation has been applied to any pos, rot or scale */
public:
	/**
	* Default constructor
	*/
	Transform();

	/**
	* Default destructor
	*/
	~Transform();

	template<class Archive>
	void serialize(Archive& ar)
	{
		_SERIALIZE_VAR(Pos, ar);
		_SERIALIZE_VAR(Scale, ar);
		_SERIALIZE_VAR(Rotation, ar);

		bUpdateModelMatrix = true;
		UpdateMatrix();
	}

	/**
	* Translates the position
	* @param offset The ammount to be added to the _pos
	*/
	void Translate(const Vector3f& offset);

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
	void SetScale(float scale);

	/**
	* Sets the individual components of _scale to the given values
	* @param scale_x _scale.x = scale_x
	* @param scale_y _scale.y = scale_y
	* @param scale_z _scale.z = scale_z
	*/
	void SetScale(float scale_x, float scale_y, float scale_z);

	/**
	* Sets the scale of the object to the given vec3 scale
	* @param scale Sets _scale to glm::vec3 scale
	*/
	void SetScale(const Vector3f& scale);

	/**
	* Rotate the object by the angle (degrees) on the given axis
	* @param angle The angle in degrees
	* @param axis The axis to rotate on
	*/
	void Rotate(float angle, const Vector3f& axis);

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
	Matrix4f& GetModelMatrix();

	/**
	* Returns the position of this object
	* @return vec3 containing the position of this object
	*/
	inline Vector3f& GetPosition()
	{
		return Pos;
	}

	/**
	* Returns the rotation of this object
	* @return vec3 containing the Euler angles of this transform
	*/
	inline Vector3f& GetRotation()
	{
		return Rotation;
	}

	/**
	* Returns the scale of this object
	* @return vec3 containing the scale of this object
	*/
	inline Vector3f& GetScale()
	{
		return Scale;
	}

	/**
	* Returns the forward direction of this object. It rotates
	* the initial default forward vector (0,0,-1) by the rotation
	* matrix - Note that this may recompute the model + rotation matrix 
	* if _update_model_matrix is set to true!
	* @return vec4 containing the way this object is facing
	*/
	inline Vector3f ForwardDirection()
	{
		static Vector4f initial_direction(0.0f,0.0f,-1.0f,1.0f);
		UpdateMatrix();
		THROW_NOT_IMPL
		return Vector3f();
		//return initial_direction;
		//return initial_direction * RotationMatrix;
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