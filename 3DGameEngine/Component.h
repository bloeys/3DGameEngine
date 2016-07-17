#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>

class System;
class Entity;

class Component
{
public:
	enum ComponentType : int
	{
		None = 0,
		Transform = 1,
		Mesh = 2
	};

	///<summary>This is automatically called when the component is added</summary>
	/// <param name="e">The entity this component belongs to</param>
	virtual void SetParentEntity(Entity &e) = 0;
	std::shared_ptr<Entity> GetEntity() const;
	ComponentType GetType() const;
	ComponentType GetRequiredTypes() const;

	Component();
	virtual ~Component();

protected:
	System* system;
	std::shared_ptr<Entity> parentEntity;
	ComponentType type;
	ComponentType requiredComponents;
};


#endif