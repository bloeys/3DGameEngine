#pragma once

#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include <vector>

class Mesh;
class MeshData;
struct OGLTexture;

class ResourceLoader
{
public:
	///<summary>Reads a file as binary and stores its data in the passed buffer</summary>
	static bool ReadFileToBuffer(const std::string &filePath, std::vector<unsigned char> &buffer);
	static bool LoadTexture(const std::string &filePath, OGLTexture &tex);
	///<summary>Tries to load a mesh from the path and loads it into the passed Mesh object. Returns whether it succeeded or not</summary>
	static bool LoadMesh(const std::string &filePath, MeshData &m);
	
	///<summary>Splits a string according to the passed delimiter and fills the vector with the string parts</summary>
	/// <param name="stringToSplit">String that will be split</param>
	/// <param name="delimiter">The character that the string will be split at</param>
	/// <param name="splitStrings">A string vector where the string parts will be placed</param>
	static void SplitString(const std::string &stringToSplit, const char delimiter, std::vector<std::string> &splitStrings);
};

#endif