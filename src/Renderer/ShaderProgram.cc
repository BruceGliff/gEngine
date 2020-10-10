#include "ShaderProgram.h"

#include <iostream>
#include <utility>

bool Renderer::ShaderProgram::CreateShader(std::string const& source, GLenum const& shader_type, GLuint& out_shaderID) const noexcept
{
    // Create shader discription of shader
    GLuint const shaderID = glCreateShader(shader_type);
    char const * code = source.c_str();
    // Load shader code
    glShaderSource(shaderID, 1, &code, nullptr);
    // Compile shader
    glCompileShader(shaderID);

    // Check if compiled successfuly
    GLint success = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        GLchar info_log[1024];
        glGetShaderInfoLog(shaderID, 1024, nullptr, info_log);
        std::cerr << "ERROR:: Compile-time: Compile shader\n" << info_log << std::endl;
        return false;
    }

    out_shaderID = shaderID;
    return true;
}

Renderer::ShaderProgram::ShaderProgram(ShaderProgram&& sp) noexcept
{
    id = sp.id;
    isCompiled = sp.isCompiled;

    sp.id = 0;
    sp.isCompiled = false;
}

Renderer::ShaderProgram& Renderer::ShaderProgram::operator=(ShaderProgram&& sp) noexcept
{
    std::swap(sp.id, id);
    std::swap(sp.isCompiled, isCompiled);
}

Renderer::ShaderProgram::~ShaderProgram()
{
    if (isCompiled)
        glDeleteProgram(id);
}

bool Renderer::ShaderProgram::IsCompiled() const noexcept
{
    return isCompiled;
}

bool Renderer::ShaderProgram::use() const noexcept
{
    glUseProgram(id);
    return true;
}

Renderer::ShaderProgram::ShaderProgram(std::string const& vertex_shader, std::string const& fragment_shader) noexcept
{
    GLuint vsID = 0;
    GLuint fsID = 0;

    isCompiled = CreateShader(vertex_shader, GL_VERTEX_SHADER, vsID);
    if (!isCompiled)
    {
        std::cerr << "ERROR:: Can not create vertex sheder" << std::endl;
        return;
    }
    isCompiled = CreateShader(fragment_shader, GL_FRAGMENT_SHADER, fsID);
    if (!isCompiled)
    {
        std::cerr << "ERROR:: Can not create fragment sheder" << std::endl;
        glDeleteShader(vsID);
        return;
    }

    // Create program and link shaders
    id = glCreateProgram();
    glAttachShader(id, vsID);
    glAttachShader(id, fsID);
    glLinkProgram(id);

    // Check program state
    GLint success = 0;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar info_log[1024];
        glGetProgramInfoLog(id, 1024, nullptr, info_log);
        std::cerr << "ERROR:: Link-time: SHaderProgram\n" << info_log << std::endl;
        isCompiled = false;
    }

    glDeleteShader(vsID);
    glDeleteShader(fsID);
}
