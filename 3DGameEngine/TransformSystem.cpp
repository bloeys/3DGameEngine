#include "TransformSystem.h"
#include "Component.h"
#include "Entity.h"
#include "Printer.h"
#include "MyTransform.h"

TransformSystem::TransformSystem()
{
	sysType = SystemType::TransformSystem;
	requiredComponents = Component::ComponentType::Transform;
	AddToActiveSystems(*this);
}

void TransformSystem::Update()
{

}

void TransformSystem::AddComponent(Entity &parentEntity)
{
	//If the entity has the correct components and its not already added to our system then add it
	if (parentEntity.HasComponent(requiredComponents) && transforms.find(parentEntity.GetId()) == transforms.end())
		transforms[parentEntity.GetId()] = (MyTransform*)parentEntity.GetComponent(Component::ComponentType::Transform);
	else
		Printer::PrintError("Entity: " + std::to_string(parentEntity.GetId()) + " Doesn't have transform component");
}

Component* TransformSystem::GetComponent(const unsigned int entityID)
{
	if (transforms.find(entityID) != transforms.end())
		return transforms[entityID];

	return nullptr;
}

void TransformSystem::DeleteComponent(Entity &parentEntity)
{
	if (transforms.find(parentEntity.GetId()) != transforms.end())
		transforms.erase(parentEntity.GetId());
}

TransformSystem::~TransformSystem()
{

}