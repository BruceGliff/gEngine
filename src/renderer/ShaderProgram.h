#pragma once

#include <string>

#include <glm/mat4x4.hpp>

namespace NSRenderer {

class ShaderProgram final {
    // Flag if Shaders is compiled
    bool isCompiled = false;
    // Id of the shader program
    unsigned int id = 0;

    //Create Shader from source code. if success return 1. return ShaderID via out_shaderID
    bool CreateShader(std::string const& source, unsigned int const& shader_type, unsigned int& out_shaderID) const noexcept;


public:
    ShaderProgram()                                    = delete;
    ShaderProgram(ShaderProgram const&)                = delete;
    ShaderProgram& operator= (ShaderProgram const&) = delete;
    ShaderProgram(ShaderProgram&&)                noexcept;
    ShaderProgram& operator= (ShaderProgram&&)    noexcept;
    ~ShaderProgram();
    // Create sheder program with vertex and flagment sheders. Has state IsCompiled()
    ShaderProgram(std::string const& vertex_shader, std::string const& fragment_shader) noexcept;

    // Check if Program in the appropriate state
    bool IsCompiled() const noexcept;
    // Drawing
    void Use() const noexcept;
    // set an id fo texture for uniform variable in fragment shader "tex". Also text is a name
    // value is a slot value at shader program. if there 1 texture, then value 0, if there if second - then 1 ... 
    void SetInt(char const * name, int const value) const noexcept;

    // load mat4 by name
    void setMat4(char const * name, glm::mat4 const& mat) const noexcept;

    // load vec3 by name
    void setVec3(char const * name, glm::vec3 const& vec) const noexcept;

    // load vec3 by name
    void setVec4(char const * name, glm::vec4 const& vec) const noexcept;

    // load float by name
    void setFloat(char const * name, float const& fl) const noexcept;
};

} //namespace NSRenderer 
