#pragma once

#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include <string>
#include <glm/fwd.hpp>

namespace Printer
{
	void Print(const std::string &m);

	///<summary>Prints the passed message with the prefix 'ERROR:'</summary>
	/// <param name="haltEngine">Whether to temporarly halt engine execution</param>
	void PrintError(const std::string &m, bool haltEngine = false);
	void Print(int x);
	void Print(float x);
	void Print(double x);
	void Print(const glm::ivec2 &v);
	void Print(const glm::ivec3 &v);
	void Print(const glm::vec2 &v);
	void Print(const glm::vec3 &v);
	void Print(const glm::quat &q);
	void Print(const glm::mat4x4 &m4);
}

#endif // !PRINTER_H