#include <fstream>
#include <map>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "GLSLProgram.h"
#include "Printer.h"

GLSLProgram::GLSLProgram() : attribCount(0), programID(0), vertShaderID
(0), fragShaderID(0)
{
}

void GLSLProgram::CompileShader(const std::string &vertShaderPath, const std::string &fragShaderPath)
{
	//Create shader program and get its ID
	programID = glCreateProgram();

	//Create vertex and fragment shaders
	vertShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (vertShaderID == 0)
		Printer::PrintError("Failed to create vertex shader", true);

	fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragShaderID == 0)
		Printer::PrintError("Failed to create vertex shader", true);

	//Compile shaders
	CompileShaderPart(vertShaderPath, vertShaderID);
	CompileShaderPart(fragShaderPath, fragShaderID);
}

void GLSLProgram::CompileShaderPart(const std::string & filePath, const GLuint id)
{
	//Load and read vertex shader
	std::ifstream vertexFile(filePath);
	if (vertexFile.fail())
		Printer::PrintError("Failed to open " + filePath);

	std::string fileContent = "";
	std::string line = "";

	//Read all lines
	while (std::getline(vertexFile, line))
	{
		fileContent += line + "\n";
	}
	vertexFile.close();

	//Compile
	const char* contentPtr = fileContent.c_str();	//Put into array of characters to be able to pass into the next function
	glShaderSource(id, 1, &contentPtr, nullptr);
	glCompileShader(id);

	//Get int that tells us the state of the compilation, like did it succeed or not
	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	//If compilation failed
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);	//Get the lenght of the error log that OpenGL will give us for the passed shader

		//Make an std vector of type char(to basically store a string) and of the same length as our log, so we can store the log in it
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);	//Fill the vector with the error log

		glDeleteShader(id);	//Delete shader

		//Print error and halt engine
		Printer::PrintError("Shader at " + filePath + " failed to compile.\nLOG: ");
		std::printf(&errorLog[0]);
		Printer::PrintError("LOG end", true);
	}
}

void GLSLProgram::LinkShaders()
{
	//Attach shaders to program
	glAttachShader(programID, vertShaderID);
	glAttachShader(programID, fragShaderID);

	//Link
	glLinkProgram(programID);

	//Error handling
	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);

	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &errorLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(programID);

		//Don't leak shaders either.
		glDeleteShader(vertShaderID);
		glDeleteShader(fragShaderID);

		Printer::PrintError("Shader linking failed\nLOG: ");
		std::printf(&errorLog[0]);
		Printer::PrintError("LOG end", true);
	}

	//Always detach shaders after a successful link.
	glDetachShader(programID, vertShaderID);
	glDetachShader(programID, fragShaderID);

	//Delete shaders to free resources
	glDeleteShader(vertShaderID);
	glDeleteShader(fragShaderID);
}

void GLSLProgram::AddAttribute(const std::string &attribName)
{
	glBindAttribLocation(programID, attribCount, attribName.c_str());
	attribCount++;
}

void GLSLProgram::AddUniform(const std::string &uniform)
{
	//Find uniform in shader
	GLint uniformLocation = glGetUniformLocation(programID, uniform.c_str());

	//Error handling
	if (uniformLocation == GL_INVALID_INDEX)
	{
		Printer::PrintError("Couldn't find uniform " + uniform);
		return;
	}

	//Add uniform to uniform map
	uniforms[uniform] = uniformLocation;
}

void GLSLProgram::SetUniform(const std::string &uniform, const int i)
{
	glUniform1i(uniforms[uniform], i);
}

void GLSLProgram::SetUniform(const std::string &uniform, const float f)
{
	glUniform1f(uniforms[uniform], f);
}

void GLSLProgram::SetUniform(const std::string &uniform, const double d)
{
	glUniform1d(uniforms[uniform], d);
}

void GLSLProgram::SetUniform(const std::string &uniform, const glm::vec3 &v3)
{
	glUniform3f(uniforms[uniform], v3[0], v3[1], v3[2]);
}

void GLSLProgram::SetUniform(const std::string &uniform, const glm::vec4 &v4)
{
	glUniform4f(uniforms[uniform], v4[0], v4[1], v4[2], v4[3]);
}

void GLSLProgram::SetUniform(const std::string &uniform, const glm::mat4 &m4)
{
	glUniformMatrix4fv(uniforms[uniform], 1, GL_FALSE, &m4[0][0]);
}

void GLSLProgram::Use()
{
	//Tell OpenGl to use this shader
	glUseProgram(programID);

	//Enable all attributes
	for (int i = 0; i < attribCount; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::UnUse()
{
	//Tell openGL to stop using this shader
	glUseProgram(0);

	//Disable attributes
	for (int i = 0; i < attribCount; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

GLSLProgram::~GLSLProgram()
{
}