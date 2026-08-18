#pragma once

#include <fstream>
#include <sstream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Shader
{   
public:
    Shader(std::string vertPath, std::string fragPath);
    void Use();
    unsigned int ShaderProgram;
};