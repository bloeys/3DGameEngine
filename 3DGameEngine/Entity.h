#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <memory>
#include "Component.h"

class Entity
{
public:
	bool active;
	
	unsigned GetId() const;
	void AddComponent(Component* newComp);
	void RemoveComponent(Component* comp);
	std::shared_ptr<Component> GetComponent(Component::ComponentType type);
	bool HasComponent(Component::ComponentType type);
	void Destroy();

	//template <class compType>
	//std::shared_ptr<compType> AddComponent()
	//{
	//	compType *c = new compType;

	//	//If the type is a component create and add to list of components
	//	if (dynamic_cast<Component*>(c))
	//	{
	//		components.emplace_back(c);
	//		return std::make_shared<compType>(*c);
	//	}
	//	
	//	else
	//	{
	//		delete c;
	//		return nullptr;
	//	}
	//}

	//template <class compType>	//Type of component
	//std::shared_ptr<compType> GetComponent()
	//{
	//	//If not a component stop
	//	if (std::is_base_of<Component, compType>())
	//	{
	//		//If the component is found turn it into a shared pointer and return
	//		for (int i = 0; i < components.size(); i++)
	//		{
	//			if (compType* comp = dynamic_cast<compType*>(components[i]))
	//				return std::make_shared<compType>(*comp);
	//		}
	//	}
	//	return nullptr;
	//}

	Entity();
	~Entity();

private:
	unsigned int id;
	std::vector<Component*> components;
	Component::ComponentType containedTypes;
};

#endif // !ENTITY_H