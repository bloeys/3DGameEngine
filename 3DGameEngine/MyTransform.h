#pragma once

#ifndef MYTRANSFORM_H
#define MYTRANSFORM_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

class MyTransform
{
public:
	//Translation
	void Translate(const glm::vec3 &translation);
	void Translate(const float x, const float y, const float z);
	void SetPosition(const glm::vec3 &newPos);
	void SetPosition(const float x, const float y, const float z);
	inline glm::vec3 GetPos() const;

	//Rotation
	void Rotate(const glm::vec3 &rotation);
	void Rotate(const float x, const float y, const float z);
	void Rotate(const float degrees, const glm::vec3 &rotationAxis);
	void SetRotation(const glm::quat newRot);
	void SetRotation(const glm::vec3 newRot);
	void SetRotation(const float x, const float y, const float z);
	inline glm::quat GetRot() const;

	//Scale
	void SetScale(const glm::vec3 &newScale);
	void SetScale(const float x, const float y, const float z);
	inline glm::vec3 GetScale() const;

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