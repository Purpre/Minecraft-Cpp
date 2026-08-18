#include <engine/core/shader.hpp>

using std::string;

string ReadFile(string path)
{
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

Shader::Shader(string vertPath, string fragPath)
{
    string vertCode = ReadFile(vertPath);
    string fragCode = ReadFile(fragPath);

    const char *vertSRC = vertCode.c_str();
    const char *fragSRC = fragCode.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertSRC, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragSRC, NULL);
    glCompileShader(fragmentShader);

    Shader::ShaderProgram = glCreateProgram();
    glAttachShader(ShaderProgram, vertexShader);
    glAttachShader(ShaderProgram, fragmentShader);
    glLinkProgram(ShaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Use()
{
    glUseProgram(ShaderProgram);
}