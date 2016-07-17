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
	if (parentEntity.HasComponent(requiredComponents) && systemComponents.find(parentEntity.GetId()) == systemComponents.end())
		systemComponents[parentEntity.GetId()] = std::make_unique<MyTransform>(*((MyTransform*)parentEntity.GetComponent(requiredComponents).get()));
	else
		Printer::PrintError("Entity: " + std::to_string(parentEntity.GetId()) + " Doesn't have transform component");
}

void TransformSystem::RemoveComponent(Entity &parentEntity)
{
	if (systemComponents.find(parentEntity.GetId()) != systemComponents.end())
		systemComponents.erase(parentEntity.GetId());
}

TransformSystem::~TransformSystem()
{

}