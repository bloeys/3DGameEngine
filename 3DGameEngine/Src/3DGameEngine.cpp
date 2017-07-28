#include "3DGameEngine.h"
#include "EngineCore.h"

EngineCore *engineCore;

int main()
{
	engineCore = new EngineCore();
	engineCore->Start();
}