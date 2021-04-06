#include "ShaderProgram.h"
#include "debug/debug.h"

#include <iostream>
#include <utility>

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

bool Renderer::ShaderProgram::CreateShader(std::string const& source, unsigned int const& shader_type, unsigned int & out_shaderID) const noexcept
{
    // Create shader discription of shader
    GLuint const shaderID = glCreateShader(shader_type);
    if (!shaderID)
    {
        GLchar info_log[1024];
        glGetShaderInfoLog(shaderID, 1024, nullptr, info_log);
        gWARNING(std::string{ "Creating shader failed " } + info_log);
        return false;
    }
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
        gWARNING(std::string{ "Compile shader failed " } + info_log);
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

    return *this;
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

void Renderer::ShaderProgram::Use() const noexcept
{
    glUseProgram(id);
}

void Renderer::ShaderProgram::SetInt(std::string const& name, int const value) const noexcept
{
    // By id and name get location of uniform variable
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Renderer::ShaderProgram::setVec3(std::string const name, glm::vec3 const& vec) const noexcept
{
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(vec));
}

void Renderer::ShaderProgram::setFloat(std::string const name, float const& fl) const noexcept
{
    glUniform1fv(glGetUniformLocation(id, name.c_str()), 1, &fl);
}

void Renderer::ShaderProgram::setMat4(std::string const& name, glm::mat4 const& mat) const noexcept
{
    // By id and name get location of uniform variable
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

Renderer::ShaderProgram::ShaderProgram(std::string const& vertex_shader, std::string const& fragment_shader) noexcept
{
    GLuint vsID = 0;
    GLuint fsID = 0;

    isCompiled = CreateShader(vertex_shader, GL_VERTEX_SHADER, vsID);
    if (!isCompiled)
    {
        gWARNING("Can not create vertex sheder");
        return;
    }
    isCompiled = CreateShader(fragment_shader, GL_FRAGMENT_SHADER, fsID);
    if (!isCompiled)
    {
        gWARNING("Can not create fragment sheder");
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
        gWARNING(std::string{"Cannot ling shader program "} + info_log);
        isCompiled = false;
    }

    glDeleteShader(vsID);
    glDeleteShader(fsID);
}
