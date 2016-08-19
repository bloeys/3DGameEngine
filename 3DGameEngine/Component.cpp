#include "Component.h"
#include "Entity.h"
#include "System.h"

Component::Component()
{
}

std::shared_ptr<Entity> Component::GetEntity() const
{
	return parentEntity;
}

Component::ComponentType Component::GetType() const
{
	return type;
}

uint32_t Component::GetRequiredTypes() const
{
	return requiredComponents;
}

Component::~Component()
{
}