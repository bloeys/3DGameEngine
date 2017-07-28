#pragma once

#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <glm/fwd.hpp>

class GLSLProgram
{
public:
	void CompileShader(const std::string &vertShaderPath, const std::string &fragShaderPath);	//Compiles a new shader
	void LinkShaders();	//Links the shader parts(must be called after compile shader)
	void AddAttribute(const std::string &attribName);	//Add an attribute(All attribs must be set before linking)
	void AddUniform(const std::string &uniform);	//Adds uniforms(After linking

	//Updates uniform value
	void SetUniform(const std::string &uniform, const int i);
	void SetUniform(const std::string &uniform, const float f);
	void SetUniform(const std::string &uniform, const double d);
	void SetUniform(const std::string &uniform, const glm::vec3 &v3);
	void SetUniform(const std::string &uniform, const glm::vec4 &v4);
	void SetUniform(const std::string &uniform, const glm::mat4 &m4);
//	void SetUniform(const std::string &uniform, const glm::mat4 &m4);

	//Start/Stop using shader
	void Use();
	void UnUse();

	GLSLProgram();
	~GLSLProgram();

private:
	std::unordered_map<std::string, GLint> uniforms;	//Store uniforms for quick access
	int attribCount;
	GLuint programID;
	GLuint vertShaderID;
	GLuint fragShaderID;

	void CompileShaderPart(const std::string & filePath, const GLuint id);
};