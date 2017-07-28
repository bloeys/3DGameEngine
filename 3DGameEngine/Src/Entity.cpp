#include "Entity.h"
#include "EntityManager.h"
#include "Printer.h"
#include "Mesh.h"

Entity::Entity() : active(true)
{
	id = EntityManager::GetUniqueID();
	EntityManager::AddEntity(*this);
}

unsigned Entity::GetId() const
{
	return id;
}

void Entity::AddComponent(Component* newComp)
{
	//If we already have this type return
	if (HasComponent(newComp->GetType()))
		return;

	containedTypes = (containedTypes | newComp->GetType());	//Add this component to our contained components
	components.emplace_back(newComp);
	newComp->SetParentEntity(*this);
}

void Entity::DeleteComponent(Component* comp)
{
	if (!HasComponent(comp->GetType()))
		return;

	for (size_t i = 0; i < components.size(); i++)
	{
		if (components[i] == comp)
		{
			//TODO: Implement Remove Component Function for Entity
		}
	}
}

Component* Entity::GetComponent(Component::ComponentType type)
{
	//If we don't have a component return a null
	if (!HasComponent(type))
		return nullptr;

	for (size_t i = 0; i < components.size(); i++)
		if (components[i]->GetType() == type)
			return components[i];
}

bool Entity::HasComponent(Component::ComponentType type)
{
	return containedTypes & type;
}

bool Entity::HasComponent(uint32_t types)
{
	return containedTypes & types;
}

void Entity::Destroy()
{
	EntityManager::DestroyEntity(*this);
}

Entity::~Entity()
{
}