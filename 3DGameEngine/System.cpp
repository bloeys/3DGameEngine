#include "System.h"
#include "Entity.h"

std::unordered_map<System::SystemType, std::unique_ptr<System>> System::activeSystems;

System::System()
{
}

System::SystemType System::GetSystemtype()
{
	return sysType;
}

void System::AddToSystem(Entity &e, SystemType t)
{
	if (activeSystems.find(t) != activeSystems.end())
		activeSystems[t]->AddComponent(e);
}

void System::RemoveFromSystem(Entity &e, SystemType t)
{
	if (activeSystems.find(t) != activeSystems.end())
		activeSystems[t]->DeleteComponent(e);
}

void System::UpdateSystem(SystemType t)
{
	if (activeSystems.find(t) != activeSystems.end())
		activeSystems[t]->Update();
}

void System::AddToActiveSystems(System &sys)
{
	if (activeSystems.find(sys.GetSystemtype()) == activeSystems.end())
		activeSystems[sys.GetSystemtype()] = std::move(std::unique_ptr<System>(&sys));
}

System::~System()
{
}