#include <glm/gtc/matrix_transform.hpp>
#include "MyTransform.h"
#include "Printer.h"
#include "GameWindow.h"
#include "TransformSystem.h"
#include "Entity.h"

float MyTransform::FOV = 75.0;
float MyTransform::width = GameWindow::WINDOWWIDTH;
float MyTransform::height = GameWindow::WINDOWHEIGHT;
float MyTransform::zNear = 1;
float MyTransform::zFar = 1000;

MyTransform::MyTransform() : pos(0, 0, 0), rot(glm::vec3(0, 0, 0)), scale(1, 1, 1), hasChanged(true)
{
	type = ComponentType::Transform;
	requiredComponents = ComponentType::None;
	
	SetPosition(pos);
}

MyTransform::MyTransform(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale) : hasChanged(true)
{
	SetPosition(position);
	SetRotation(rotation);
	SetScale(scale);
}

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

void MyTransform::SetPosition(const glm::vec3 &newPos)
{
	pos = -newPos;
	hasChanged = true;
}

void MyTransform::SetPosition(const float x, const float y, const float z)
{
	pos[0] = -x;
	pos[1] = -y;
	pos[2] = -z;
	hasChanged = true;
}

glm::vec3 MyTransform::GetPos() const
{
	return pos;
}

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

glm::quat MyTransform::GetRot() const
{
	return rot;
}

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

glm::vec3 MyTransform::GetScale() const
{
	return scale;
}

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

glm::mat4 MyTransform::GetProjectedTransformationMatrix()
{
	return glm::perspectiveFov(FOV, width, height, zNear, zFar) * GetTransformationMatrix();
}

void MyTransform::SetProjection(float fov, float width, float height, float nearClipping, float farClipping)
{
	MyTransform::FOV = fov;
	MyTransform::width = width;
	MyTransform::height = height;
	MyTransform::zNear = nearClipping;
	MyTransform::zFar = farClipping;
}

void MyTransform::SetParentEntity(Entity &e)
{
	if (!parentEntity)
	{
		parentEntity = std::make_shared<Entity>(e);
		System::AddToSystem(e, System::SystemType::TransformSystem);
	}
}

MyTransform::~MyTransform()
{
}