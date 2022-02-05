#include "ShaderProgram.h"
#include "../debug/debug.h"

#include <utility>

#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

using namespace NSRenderer;

bool ShaderProgram::CreateShader(std::string const& source, unsigned int const& shader_type, unsigned int & out_shaderID) const noexcept {
    // Create shader discription of shader
    GLuint const shaderID = glCreateShader(shader_type);
    if (!shaderID) {
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

    if (!success) {
        GLchar info_log[1024];
        glGetShaderInfoLog(shaderID, 1024, nullptr, info_log);
        gWARNING(std::string{ "Compile shader failed " } + info_log);
        return false;
    }

    out_shaderID = shaderID;
    return true;
}

ShaderProgram::ShaderProgram(ShaderProgram&& sp) noexcept {
    id = sp.id;
    isCompiled = sp.isCompiled;

    sp.id = 0;
    sp.isCompiled = false;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& sp) noexcept {
    std::swap(sp.id, id);
    std::swap(sp.isCompiled, isCompiled);
    return *this;
}

ShaderProgram::~ShaderProgram() {
    if (isCompiled)
        glDeleteProgram(id);
}

bool ShaderProgram::IsCompiled() const noexcept {
    return isCompiled;
}

void ShaderProgram::Use() const noexcept {
    glUseProgram(id);
}

void ShaderProgram::SetInt(char const * name, int const value) const noexcept {
    // By id and name get location of uniform variable
    GLint location = glGetUniformLocation(id, name);
    if (location == -1)
        gWARNING(std::string{"Cannot find uniform location of: "} + name);
    glUniform1i(location, value);
}

// TODO do checks
void ShaderProgram::setVec3(char const * name, glm::vec3 const& vec) const noexcept {
    glUniform3fv(glGetUniformLocation(id, name), 1, glm::value_ptr(vec));
}

void ShaderProgram::setVec4(char const * name, glm::vec4 const& vec) const noexcept {
    glUniform4fv(glGetUniformLocation(id, name), 1, glm::value_ptr(vec));
}


void ShaderProgram::setFloat(char const * name, float const& fl) const noexcept {
    glUniform1fv(glGetUniformLocation(id, name), 1, &fl);
}

void ShaderProgram::setMat4(char const * name, glm::mat4 const& mat) const noexcept {
    // By id and name get location of uniform variable
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(mat));
}

ShaderProgram::ShaderProgram(std::string const& vertex_shader, std::string const& fragment_shader) noexcept {
    GLuint vsID = 0;
    GLuint fsID = 0;

    isCompiled = CreateShader(vertex_shader, GL_VERTEX_SHADER, vsID);
    if (!isCompiled) {
        gWARNING("Can not create vertex sheder");
        return;
    }
    isCompiled = CreateShader(fragment_shader, GL_FRAGMENT_SHADER, fsID);
    if (!isCompiled) {
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
    if (!success) {
        GLchar info_log[1024];
        glGetProgramInfoLog(id, 1024, nullptr, info_log);
        gWARNING(std::string{"Cannot ling shader program "} + info_log);
        isCompiled = false;
    }

    glDeleteShader(vsID);
    glDeleteShader(fsID);
}
