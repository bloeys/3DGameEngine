#include "MeshSystem.h"
#include "Component.h"
#include "Entity.h"
#include "Printer.h"

MeshSystem::MeshSystem()
{
	sysType = SystemType::RenderSystem;
	requiredComponents = Component::ComponentType::Mesh;
	AddToActiveSystems(*this);
}

void MeshSystem::Update()
{

}

void MeshSystem::AddComponent(Entity & parentEntity)
{
	if (parentEntity.HasComponent(requiredComponents) && meshes.find(parentEntity.GetId()) == meshes.end())
		meshes[parentEntity.GetId()] = std::make_unique<Mesh>(*((Mesh*)parentEntity.GetComponent(requiredComponents).get()));
}

void MeshSystem::RemoveComponent(Entity & parentEntity)
{
}

MeshSystem::~MeshSystem()
{
}