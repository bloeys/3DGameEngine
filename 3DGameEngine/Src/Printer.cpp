#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Printer.h"
#include "3DGameEngine.h"
#include "EngineCore.h"
#include <iostream>

void Printer::Print(const std::string &m)
{
	std::cout << m << std::endl;
}

void Printer::PrintError(const std::string &m, bool haltEngine)
{
	std::cout << std::endl << "ERROR: " << m << std::endl;

	if (haltEngine)
		engineCore->HaltEngine();
}

void Printer::Print(int x)
{
	std::cout << x << std::endl;
}

void Printer::Print(float x)
{
	int oldPrec = std::cout.precision();
	std::cout.precision(12);
	std::cout << x << std::endl;
	std::cout.precision(oldPrec);
}

void Printer::Print(double x)
{
	int oldPrec = std::cout.precision();
	std::cout.precision(14);
	std::cout << x << std::endl;
	std::cout.precision(oldPrec);
}

void Printer::Print(const glm::ivec2 &v)
{
	std::cout << "V2i(" << v[0] << ", " << v[1] << ")" << std::endl;
}

void Printer::Print(const glm::ivec3 &v)
{
	std::cout << "V3i(" << v[0] << ", " << v[1] << ", " << v[2] << ")" << std::endl;
}

void Printer::Print(const glm::vec2 &v)
{
	int oldPrec = std::cout.precision();
	std::cout.precision(14);
	std::cout << "V2f(" << v[0] << ", " << v[1] << ")" << std::endl;
	std::cout.precision(oldPrec);
}

void Printer::Print(const glm::vec3 &v)
{
	int oldPrec = std::cout.precision();
	std::cout.precision(14);
	std::cout << "V3f(" << v[0] << ", " << v[1] << ", " << v[2] << ")" << std::endl;
	std::cout.precision(oldPrec);
}

void Printer::Print(const glm::quat &q)
{
	int oldPrec = std::cout.precision();
	std::cout.precision(14);
	std::cout << "Q4(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")" << std::endl;
	std::cout.precision(oldPrec);
}

void Printer::Print(const glm::mat4x4 &m4)
{
	std::cout << std::endl;
	std::cout << m4[0][0] << ", " << m4[0][1] << ", " << m4[0][2] << ", " << m4[0][3] << ", " << std::endl;	//Row 1
	std::cout << m4[1][0] << ", " << m4[1][1] << ", " << m4[1][2] << ", " << m4[1][3] << ", " << std::endl;	//Row 2
	std::cout << m4[2][0] << ", " << m4[2][1] << ", " << m4[2][2] << ", " << m4[2][3] << ", " << std::endl;	//Row 3
	std::cout << m4[3][0] << ", " << m4[3][1] << ", " << m4[3][2] << ", " << m4[3][3] << ", " << std::endl;	//Row 4
	std::cout << std::endl;
}