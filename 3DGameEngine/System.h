#pragma once

#ifndef SYSTEM_H
#define SYSTEM_H

#include <unordered_map>
#include <memory>
#include "Component.h"

class Entity;
enum ComponentType;

class System
{
public:
	
	enum SystemType : int
	{
		TransformSystem = 1,
		RenderSystem = 2
	};

	SystemType GetSystemtype();

	static void AddToSystem(Entity &e, SystemType t);
	static void RemoveFromSystem(Entity &e, SystemType t);

	System();
	virtual ~System();

protected:
	SystemType sysType;
	Component::ComponentType requiredComponents;
	static std::unordered_map<SystemType, std::unique_ptr<System>> activeSystems;

	void AddToActiveSystems(System &sys);

	virtual void Update() = 0;
	virtual void AddComponent(Entity &entity) = 0;
	virtual void RemoveComponent(Entity &entity) = 0;
};

#endif