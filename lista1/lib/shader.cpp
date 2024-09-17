#include "shader.h"
#include <iostream>

void Shader::setTransformSource(std::string &geometry_source) {
    this->geometry_source = geometry_source;
}

void Shader::setTesselationSource(std::string &tesselation_source) {
    this->tesselation_source = tesselation_source;
}

std::optional<GLuint> Shader::compile() {
    // Vertex
    std::optional<GLuint> vert_shader = Shader::generic_compile(vert_source, GL_VERTEX_SHADER);
    if (!vert_shader.has_value()) {
        return std::nullopt;
    }
    // Fragment
    std::optional<GLuint> frag_shader = Shader::generic_compile(frag_source, GL_FRAGMENT_SHADER);
    if (!frag_shader.has_value()) {
        return std::nullopt;
    }

    std::optional<GLuint> geometry_shader;

    std::optional<GLuint> tesselation_shader;

    if (this->geometry_source.has_value()) {
        geometry_shader = Shader::generic_compile(geometry_source.value(),  GL_GEOMETRY_SHADER);
        if (!geometry_shader.has_value()) {
            return std::nullopt;
        }
    }
    if (this->tesselation_source.has_value()) {
        tesselation_shader = Shader::generic_compile(tesselation_source.value(), GL_TESS_CONTROL_SHADER);
        if (!tesselation_shader.has_value()) {
            return std::nullopt;
        }
    }

    GLint result = 0;
    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vert_shader.value());

    glAttachShader(shaderProgram, frag_shader.value());

    if (geometry_shader) {
        glAttachShader(shaderProgram, geometry_shader.value());
    }
    if (tesselation_shader) {
        glAttachShader(shaderProgram, tesselation_shader.value());
    }
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &result);
        std::string log(result, ' ');
        glGetProgramInfoLog(shaderProgram, result, NULL, log.data());
        std::cerr << "Shader linking failed with error: " << log << '\n';
        return std::nullopt;
    }
    
    return shaderProgram;
}

std::optional<GLuint> Shader::generic_compile(const std::string &source, GLenum shader_type) {
    GLuint shader = glCreateShader(shader_type);
    const GLchar *cstr_source = (const GLchar *)source.c_str();
    glShaderSource(shader, 1, &cstr_source, NULL);
    glCompileShader(shader);
    GLint result = 0;
    glGetShaderiv(shader,  GL_COMPILE_STATUS, &result);
    // compilation failed
    if (!result) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &result);
        std::string log(result, ' ');
        glGetShaderInfoLog(shader, result, NULL, log.data());
        std::cerr << "Shader compilation failed with error: " << log << '\n';
        return std::nullopt;
    }
    return shader;
}
