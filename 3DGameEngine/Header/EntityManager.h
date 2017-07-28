#pragma once

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <unordered_map>
#include <memory>

class Entity;

class EntityManager
{
public:
	static void Update();
	static void AddEntity(Entity &parentEntity);
	static void DestroyEntity(Entity &parentEntity);
	static void DestroyEntity(unsigned entityID);
	static unsigned GetUniqueID();

	EntityManager();
	~EntityManager();

private:
	static std::unordered_map<unsigned int, std::unique_ptr<Entity>> entities;
};

#endif // !ENTITYMANAGER_H