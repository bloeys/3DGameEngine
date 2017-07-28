#include "3DGameEngine.h"
#include "EngineCore.h"

//Declare extern var
EngineCore *engineCore;

int main()
{
	engineCore = new EngineCore();
	engineCore->Start();
}