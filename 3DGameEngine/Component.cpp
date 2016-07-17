#include "Component.h"
#include "Entity.h"

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

Component::ComponentType Component::GetRequiredTypes() const
{
	return requiredComponents;
}

Component::~Component()
{
}