#include "Entity.h"
#include "EntityManager.h"
#include "Printer.h"

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

	containedTypes = (Component::ComponentType)(containedTypes | newComp->GetType());	//Add this component to our contained components
	components.emplace_back(newComp);
	newComp->SetParentEntity(*this);
}

void Entity::RemoveComponent(Component* comp)
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

std::shared_ptr<Component> Entity::GetComponent(Component::ComponentType type)
{
	//If we don't have a component return a null
	if (!HasComponent(type))
		return std::shared_ptr<Component>();

	for (size_t i = 0; i < components.size(); i++)
	{
		if (components[i]->GetType() == type)
		{
			return std::shared_ptr<Component>(components[i]);
		}
	}
}

bool Entity::HasComponent(Component::ComponentType type)
{
	if (containedTypes & type)
		return true;
	else
		return false;
}

void Entity::Destroy()
{
	EntityManager::DestroyEntity(*this);
}

Entity::~Entity()
{
}