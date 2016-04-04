#pragma once

#ifndef MYTRANSFORM_H
#define MYTRANSFORM_H

#include <glm/gtc/quaternion.hpp>
#include <glm/fwd.hpp>

class MyTransform
{
public:
	//Translation
	
	///<summary>Moves transform by passed amount</summary>
	void Translate(const glm::vec3 &translation);
	///<summary>Moves transform by passed amount</summary>
	void Translate(const float x, const float y, const float z);
	///<summary>Sets the position of the transform</summary>
	void SetPosition(const glm::vec3 &newPos);
	///<summary>Sets the position of the transform</summary>
	void SetPosition(const float x, const float y, const float z);
	///<summary>Returns the current position of the transform</summary>
	glm::vec3 GetPos();

	//Rotation
	void Rotate(const glm::vec3 &rotation);
	void Rotate(const float x, const float y, const float z);
	void Rotate(const float degrees, const glm::vec3 &rotationAxis);
	void SetRotation(const glm::quat newRot);
	void SetRotation(const glm::vec3 newRot);
	void SetRotation(const float x, const float y, const float z);
	glm::quat GetRot();

	//Scale
	void SetScale(const glm::vec3 &newScale);
	void SetScale(const float x, const float y, const float z);
	glm::vec3 GetScale();

	//Final transformation matrix
	glm::mat4 GetTransformationMatrix();

	MyTransform();
	MyTransform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale);
	~MyTransform();

private:
	bool hasChanged;	//Whether we need to recalculate the transformation matrix
	glm::vec3 pos;	//Position in 3D space
	glm::quat rot;	//Rotation
	glm::vec3 scale;	//Scale
	glm::mat4 transformationMatrix;
};

#endif