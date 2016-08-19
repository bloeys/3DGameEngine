#pragma once

#ifndef TRANSFORMSYSTEM_H
#define TRANSFORMSYSTEM_H

#include <unordered_map>
#include "System.h"

class MyTransform;

class TransformSystem : public System
{
public:
	virtual Component* GetComponent(const unsigned int entityID);

	TransformSystem();
	~TransformSystem();

protected:
	// Inherited via System
	virtual void Update() override;
	virtual void AddComponent(Entity &parentEntity) override;
	virtual void DeleteComponent(Entity &parentEntity) override;
	
private:
	std::unordered_map<unsigned int, MyTransform*> transforms;
};

#endif