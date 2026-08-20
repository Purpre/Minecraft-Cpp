#pragma once

#include <vector>

#include <engine/core/window.hpp>
#include <engine/core/texture.hpp>
#include <engine/core/shader.hpp>
#include <engine/core/camera.hpp>
#include <world/chunk.hpp>

class Renderer
{
public:
    Window *window = nullptr;
    Texture *texture = nullptr;
    Shader *shader = nullptr;
    Camera *camera = nullptr;

    void render(std::vector<Chunk> &chunks, float delta);
};