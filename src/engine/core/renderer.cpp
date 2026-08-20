#include <engine/core/renderer.hpp>

void Renderer::render(std::vector<Chunk> &chunks, float delta)
{
    glClearColor(0.4f, 0.6f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();
    shader->Use();

    for (Chunk &chunk : chunks)
    {
        chunk.draw();
    }

    camera->update(delta, window->win);
}