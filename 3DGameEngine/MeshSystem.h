#pragma once

#ifndef MeshSystem_H
#define MeshSystem_H

#include <unordered_map>
#include "System.h"
#include "Mesh.h"
#include "MyTransform.h"
#include "GLSLProgram.h"

class MeshSystem : public System
{
public:
	virtual Component* GetComponent(const unsigned int entityID) override;

	MeshSystem();
	~MeshSystem();

protected:
	// Inherited via System
	virtual void Update() override;
	virtual void AddComponent(Entity & parentEntity) override;
	virtual void DeleteComponent(Entity & parentEntity) override;

private:
	std::unordered_map<unsigned int, Mesh*> meshes;
	std::unordered_map<unsigned int, MyTransform*> transforms;
	GLSLProgram glp;
};

#endif // !MeshSystem_H