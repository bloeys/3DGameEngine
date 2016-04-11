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

void TransformSystem::AddComponent(Entity &entity)
{
	//If the entity has the correct components and its not already added to our system then add it
	if (entity.HasComponent(requiredComponents) && systemComponents.find(entity.GetId()) == systemComponents.end())
	{
		systemComponents[entity.GetId()] = std::make_unique<MyTransform>(*((MyTransform*)entity.GetComponent(requiredComponents).get()));
	}

	else
	{
		Printer::PrintError("Entity: " + std::to_string(entity.GetId()) + " Doesn't have transform component");
	}
}

void TransformSystem::RemoveComponent(Entity &entity)
{
	if (systemComponents.find(entity.GetId()) != systemComponents.end())
		systemComponents.erase(entity.GetId());
}

TransformSystem::~TransformSystem()
{

}