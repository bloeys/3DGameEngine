#pragma once

#ifndef MeshSystem_H
#define MeshSystem_H

#include <memory>
#include <unordered_map>
#include "System.h"
#include "Mesh.h"

class MeshSystem : public System
{
public:
	MeshSystem();
	~MeshSystem();

	// Inherited via System
	virtual void Update() override;
	virtual void AddComponent(Entity & parentEntity) override;
	virtual void RemoveComponent(Entity & parentEntity) override;

private:
	std::unordered_map<unsigned int, std::unique_ptr<Mesh>> meshes;
};

#endif // !MeshSystem_H