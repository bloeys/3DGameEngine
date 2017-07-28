#include <fstream>
#include <SOIL.h>
#include <sstream>
#include "ResourceLoader.h"
#include "Printer.h"
#include "GLTexture.h"
#include "Mesh.h"
#include "MeshData.h"

bool ResourceLoader::ReadFileToBuffer(const std::string &filePath, std::vector<unsigned char> &buffer)
{
	std::ifstream file(filePath, std::ios::binary);

	//If couldn't open file
	if (file.fail())
	{
		Printer::PrintError("Couldn't read file at: " + filePath);
		return false;
	}

	//Seek to end of file
	file.seekg(0, std::ios::end);

	//Get file size
	int fileSize = file.tellg();

	//Return to beginning
	file.seekg(0, std::ios::beg);

	//NOTE: This isn't really doing anything! is it?
	//Just remove any file header bytes
	//fileSize -= file.tellg();

	//Make the buffer (std::vector) the needed size to hold all the read data
	buffer.resize(fileSize);

	//Read a number of bytes(this no. is in 'fileSize') and put them in the buffer
	file.read((char*)&buffer[0], fileSize);

	//Close file
	file.close();

	return true;
}

bool ResourceLoader::LoadTexture(const std::string &filePath, OGLTexture &tex)
{
	std::vector<unsigned char> buffer;	//A buffer to store all the bytes of the texture in memory

	//Error
	if (!ReadFileToBuffer(filePath, buffer))
	{
		Printer::PrintError("Failed to read file while loading texture. PATH: " + filePath);
		return false;
	}

	//Get pixel data from memory and point to them
	unsigned char* pixels = SOIL_load_image_from_memory(&buffer[0], sizeof(buffer[0]) * buffer.size(), &tex.width, &tex.height, 0, SOIL_LOAD_AUTO);

	//Generate and bind
	glGenTextures(1, &tex.id);
	glBindTexture(GL_TEXTURE_2D, tex.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.width, tex.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	//Texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Unbind
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

bool ResourceLoader::LoadMesh(const std::string &filePath, MeshData &m)
{
	std::vector<std::string> splitData;
	SplitString(filePath, '.', splitData);

	//If the extention isn't obj then we throw an error
	if (splitData[splitData.size() - 1] != "obj")
	{
		Printer::PrintError("Mesh at: " + filePath + "\nisn't of type 'obj'\n");
		return false;
	}

	std::vector<Vertex> vertices;
	std::vector<int> indices;

	std::ifstream meshFile(filePath);
	if (meshFile.fail())
	{
		Printer::PrintError("Failed to open Mesh file at: " + filePath);
		return false;
	}

	std::string line = "";	//Holds a line from the mesh file
	splitData.clear();

	//Read all lines one by one
	while (std::getline(meshFile, line))
	{
		//If line is a comment or is empty skip
		if (line.length() == 0 || line[0] == '#')
			continue;

		splitData.clear();
		//If its a vertex(stof = "string to float")
		if (line[0] == 'v' &&line[1] == ' ')
		{
			SplitString(line, ' ', splitData);	//Split the line by space
			vertices.emplace_back(Vertex(std::stof(splitData[1]), std::stof(splitData[2]), std::stof(splitData[3])));	//Add a new vertex to the vertex vector
		}

		//Faces
		else if (line[0] == 'f')
		{
			SplitString(line, ' ', splitData);	//Split the line by space
			splitData.erase(splitData.begin());	//Remove the 'f' character
			std::vector<std::string> faceDataSegment;	//This will store each face, where each 3 subsequent values correspond to Vertex/Tex.Coord./Vertex Normal

			//For each face, we extract three segments of data, each containing information about a vertex(a segment looks like V/TC/VN. meanings above)
			for (size_t i = 0; i < splitData.size(); i++)
			{

				SplitString(splitData[i], '/', faceDataSegment);	//Split face part
				indices.emplace_back(std::stoi(faceDataSegment[0]) - 1);	//Take face index, but subtract one because obj files count starting at 1 not 0

				//Put texture coord and vertex normal code here

				faceDataSegment.clear();	//Clear mesh face for next run
			}
		}
	}
	meshFile.close();

	m.SetData(vertices, indices);
	return true;
}

void ResourceLoader::SplitString(const std::string &stringToSplit, const char delimiter, std::vector<std::string> &splitStrings)
{
	std::stringstream stream(stringToSplit);	//Turn this string into a stream
	std::string stringPart;

	//Move in the stream until you hit a delimiter, then put whatever characters we got in the vector, rince and repeat
	while (std::getline(stream, stringPart, delimiter))
	{
		splitStrings.emplace_back(stringPart);
	}
}