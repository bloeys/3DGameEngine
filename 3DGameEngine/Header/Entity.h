#pragma once

#include <vector>
#include "Component.h"

class Entity
{
public:
	bool active;
	
	unsigned GetId() const;
	void AddComponent(Component* newComp);
	void DeleteComponent(Component* comp);
	Component* GetComponent(Component::ComponentType type);
	bool HasComponent(Component::ComponentType type);
	bool HasComponent(uint32_t types);
	void Destroy();

	Entity();
	~Entity();

private:
	unsigned int id;
	std::vector<Component*> components;
	uint32_t containedTypes;
};