#pragma once

#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stb_image.h>

class Texture
{
public:
    Texture(std::string path);
    unsigned int texture;
    void bind();
};