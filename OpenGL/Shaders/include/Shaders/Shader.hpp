#ifndef __SHADER_HPP_INCLUDED__
#define __SHADER_HPP_INCLUDED__

#include <GLAD/glad.h>
#include <glm/glm.hpp>

#include <iostream>
#include <fstream>

#include <sstream>
#include <string>

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    ~Shader();
	// Private methods

	void use	  (); 
	void setBool  (const std::string &name, bool  value) const;
    void setInt   (const std::string &name, int   value) const;
    void setFloat (const std::string &name, float value) const;
    
	void setVec2  (const std::string &name, const glm::vec2 &value) const;
    void setVec2  (const std::string &name, float x, float y) const;
    void setVec3  (const std::string &name, const glm::vec3 &value) const;
    void setVec3  (const std::string &name, float x, float y, float z) const;
    void setVec4  (const std::string &name, const glm::vec4 &value) const;
    void setVec4  (const std::string &name, float x, float y, float z, float w); 
    
	void setMat2  (const std::string &name, const glm::mat2 &mat) const;
    void setMat3  (const std::string &name, const glm::mat3 &mat) const;
    void setMat4  (const std::string &name, const glm::mat4 &mat) const;

private:
	void checkCompileErrors(GLuint shader, std::string type);
	// Private properties
private:
	unsigned int ID;

	std::string vertexCode;
	std::string	fragmentCode;
	std::string	geometryCode;
	
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream gShaderFile;

	std::stringstream vShaderStream, fShaderStream, gShaderStream;
	
	const char* vShaderCode;
	const char* fShaderCode;

	unsigned int vertex, fragment;

	unsigned int geometry;
};

#endif // !__SHADER_HPP_INCLUDED__