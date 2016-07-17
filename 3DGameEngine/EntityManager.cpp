#include <random>
#include <chrono>
#include "EntityManager.h"
#include "Entity.h"

std::unordered_map<unsigned int, std::unique_ptr<Entity>> EntityManager::entities;

EntityManager::EntityManager()
{
}

void EntityManager::Update()
{
}

void EntityManager::AddEntity(Entity &parentEntity)
{
	if (entities.find(parentEntity.GetId()) == entities.end())
		entities[parentEntity.GetId()] = std::make_unique<Entity>(parentEntity);
}

void EntityManager::DestroyEntity(Entity &parentEntity)
{
	if (entities.find(parentEntity.GetId()) != entities.end())
		entities.erase(parentEntity.GetId());
}

void EntityManager::DestroyEntity(unsigned entityID)
{
	if (entities.find(entityID) != entities.end())
		entities.erase(entityID);
}

unsigned EntityManager::GetUniqueID()
{
	//Use current time as a seed and generate a random number
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 rand(seed);
	unsigned uniqueID = rand();

	//If the id we generated is used then generate another one
	while (entities.find(uniqueID) != entities.end())
	{
		uniqueID = rand();
	}

	return uniqueID;
}

EntityManager::~EntityManager()
{
}