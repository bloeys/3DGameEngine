#pragma once

#include <unordered_map>
#include <memory>
#include "Component.h"

class Entity;
enum ComponentType;

class System
{
public:

	enum SystemType : uint32_t
	{
		TransformSystem = 1,
		RenderSystem = 2
	};

	SystemType GetSystemtype();

	static void AddToSystem(Entity &e, SystemType t);
	static void RemoveFromSystem(Entity &e, SystemType t);
	static void UpdateSystem(SystemType t);
	virtual Component* GetComponent(const unsigned int entityID) = 0;

	System();
	virtual ~System();

protected:
	SystemType sysType;
	uint32_t requiredComponents;
	static std::unordered_map<SystemType, std::unique_ptr<System>> activeSystems;

	void AddToActiveSystems(System &sys);

	virtual void Update() = 0;
	virtual void AddComponent(Entity &parentEntity) = 0;
	virtual void DeleteComponent(Entity &parentEntity) = 0;
};