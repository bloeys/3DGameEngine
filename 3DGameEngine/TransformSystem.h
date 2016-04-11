#pragma once

#ifndef TRANSFORMSYSTEM_H
#define TRANSFORMSYSTEM_H

#include <memory>
#include <unordered_map>
#include "System.h"

class MyTransform;

class TransformSystem : public System
{
public:

	TransformSystem();
	~TransformSystem();

protected:
	// Inherited via System
	virtual void Update() override;
	virtual void AddComponent(Entity &entity) override;
	virtual void RemoveComponent(Entity &entity) override;

private:
	std::unordered_map<unsigned int, std::unique_ptr<MyTransform>> systemComponents;
};

#endif