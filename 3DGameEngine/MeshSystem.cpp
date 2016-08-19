#include "MeshSystem.h"
#include "Component.h"
#include "Entity.h"
#include "Printer.h"

MeshSystem::MeshSystem()
{
	sysType = SystemType::RenderSystem;
	requiredComponents = Component::ComponentType::Mesh | Component::ComponentType::Transform;
	AddToActiveSystems(*this);

	glp.CompileShader(R"(Resources/Shaders/SimpleColorShader.vert)", R"(Resources/Shaders/SimpleColorShader.frag)");
	glp.AddAttribute("vertPos");
	glp.AddAttribute("vertColor");
	glp.LinkShaders();
	glp.AddUniform("transformation");
}

void MeshSystem::Update()
{
	glp.Use();
	for (auto i : meshes)
	{
		glp.SetUniform("transformation", transforms[i.first]->GetProjectedTransformationMatrix());
		i.second->Draw();
	}
	glp.UnUse();
}

void MeshSystem::AddComponent(Entity & parentEntity)
{
	if (parentEntity.HasComponent(requiredComponents) && meshes.find(parentEntity.GetId()) == meshes.end() && transforms.find(parentEntity.GetId()) == transforms.end())
	{
		meshes[parentEntity.GetId()] = (Mesh*)parentEntity.GetComponent(Component::ComponentType::Mesh);
		transforms[parentEntity.GetId()] = (MyTransform*)parentEntity.GetComponent(Component::ComponentType::Transform);
	}
}

Component* MeshSystem::GetComponent(const unsigned int entityID)
{
	if (meshes.find(entityID) != meshes.end())
		return meshes[entityID];

	return nullptr;
}

void MeshSystem::DeleteComponent(Entity & parentEntity)
{
}

MeshSystem::~MeshSystem()
{
}