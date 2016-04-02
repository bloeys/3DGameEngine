#include "MyTransform.h"
#include <glm/gtc/matrix_transform.hpp>
#include"Printer.h"

MyTransform::MyTransform() : pos(0, 0, 0), rot(glm::vec3(0, 0, 0)), scale(1, 1, 1), hasChanged(true)
{
	SetPosition(pos);
}

MyTransform::MyTransform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale) : hasChanged(true)
{
	SetPosition(pos);
	SetRotation(rotation);

}

///Moves transform by passed amount
void MyTransform::Translate(const glm::vec3 &translation)
{
	pos += translation;
	hasChanged = true;
}

void MyTransform::Translate(const float x, const float y, const float z)
{
	pos[0] += x;
	pos[1] += y;
	pos[2] += z;
	hasChanged = true;
}

///Sets the position of the transform to the new passed position
void MyTransform::SetPosition(const glm::vec3 &newPos)
{
	pos = newPos;
	hasChanged = true;
}

void MyTransform::SetPosition(const float x, const float y, const float z)
{
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	hasChanged = true;
}

///Returns current position
glm::vec3 MyTransform::GetPos() const
{
	return pos;
}

///Rotate transform by amount
void MyTransform::Rotate(const glm::vec3 &rotation)
{
	//Angles are inverted because for some reason passing positive angles rotates anticlockwise, so we reverse that
	rot = glm::quat(glm::vec3(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(-rotation.z))) * rot;
	hasChanged = true;
}

void MyTransform::Rotate(const float degrees, const glm::vec3 &rotationAxis)
{
	rot = glm::rotate(rot, glm::radians(-degrees), rotationAxis);
	hasChanged = true;
}

void MyTransform::Rotate(const float x, const float y, const float z)
{
	rot = glm::quat(glm::vec3(glm::radians(x), glm::radians(y), glm::radians(-z))) * rot;
	hasChanged = true;
}

///Sets the rotation to the passed rotation
void MyTransform::SetRotation(const glm::quat newRot)
{
	rot = newRot;
	hasChanged = true;
}

void MyTransform::SetRotation(const glm::vec3 newRot)
{
	rot = glm::quat(glm::vec3(glm::radians(newRot.x), glm::radians(newRot.y), glm::radians(-newRot.z)));
	hasChanged = true;
}

void MyTransform::SetRotation(const float x, const float y, const float z)
{
	rot = glm::quat(glm::vec3(glm::radians(x), glm::radians(y), glm::radians(-z)));
	hasChanged = true;
}

///Returns the current rotation
glm::quat MyTransform::GetRot() const
{
	return rot;
}

///Sets the scale of the transform
void MyTransform::SetScale(const glm::vec3 &newScale)
{
	scale = newScale;
	hasChanged = true;
}

void MyTransform::SetScale(const float x, const float y, const float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
	hasChanged = true;
}

///Returns the scale of the object
glm::vec3 MyTransform::GetScale() const
{
	return scale;
}

///Returns the final transformation matrix containing translation+rotation+scale
glm::mat4 MyTransform::GetTransformationMatrix()
{
	//Only if something has changed (like position) do we calculate the transformation matrix
	if (hasChanged)
	{
		//Translation: translate from an identity matrix. Rotation: turn the rot quaternion into a matrix4. Scale an identity matrix
		transformationMatrix = (glm::translate(glm::mat4(1), pos)) * glm::mat4_cast(rot) * glm::scale(glm::mat4(1), scale);
		hasChanged = false;
	}

	return transformationMatrix;
}

MyTransform::~MyTransform()
{
}