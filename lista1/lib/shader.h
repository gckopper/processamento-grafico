#include <filesystem>
#include <fstream>
#include <iostream>
#include <glad/gl.h>
#include <optional>

class Shader {
    public:
        Shader(std::filesystem::path &vertex_path, std::filesystem::path &frag_path): vert_path(vertex_path), tesselation_path(), transform_path(), frag_path(frag_path) {}
        void setTransformPath(std::filesystem::path &transform_path) {
            this->transform_path = transform_path;
        }
        void setTesselationPath(std::filesystem::path &tesselation_path) {
            this->tesselation_path = tesselation_path;
        }
        std::optional<GLuint> compile() {
            if (!std::filesystem::exists(vert_path)) {
                std::cerr << "Unable to find vertex shader at: " << vert_path << '\n';
                return std::nullopt;
            }
            if (!std::filesystem::exists(frag_path)) {
                std::cerr << "Unable to find fragment shader at: " << frag_path << '\n';
                return std::nullopt;
            }
            if (transform_path.has_value()) {
                if (!std::filesystem::exists(transform_path.value())) {
                    std::cerr << "Unable to find transform shader at: " << transform_path.value() << '\n';
                    return std::nullopt;
                }
            }
            if (tesselation_path.has_value()) {
                if (!std::filesystem::exists(tesselation_path.value())) {
                    std::cerr << "Unable to find tesselation shader at: " << tesselation_path.value() << '\n';
                    return std::nullopt;
                }
            }

            // Vertex
            std::optional<GLuint> vert_shader = generic_compile(vert_path);
            if (!vert_shader.has_value()) {
                return std::nullopt;
            }
            // Fragment
            std::optional<GLuint> frag_shader = generic_compile(frag_path);
            if (!frag_shader.has_value()) {
                return std::nullopt;
            }

            std::optional<GLuint> transform_shader = std::nullopt;

            std::optional<GLuint> tesselation_shader = std::nullopt;

            if (this->transform_path.has_value()) {
                transform_shader = generic_compile(transform_path.value());
                if (!transform_shader.has_value()) {
                    return std::nullopt;
                }
            }
            if (this->tesselation_path.has_value()) {
                tesselation_shader = generic_compile(tesselation_path.value());
                if (!tesselation_shader.has_value()) {
                    return std::nullopt;
                }
            }

            GLuint shaderProgram = glCreateProgram();

            glAttachShader(shaderProgram, vert_shader.value());
            glAttachShader(shaderProgram, frag_shader.value());
            if (transform_shader.has_value()) {
                glAttachShader(shaderProgram, transform_shader.value());
            }
            if (tesselation_shader.has_value()) {
                glAttachShader(shaderProgram, tesselation_shader.value());
            }
            glLinkProgram(shaderProgram);

            GLint result = 0;
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
            if (!result) {
                glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &result);
                std::string log(result, ' ');
                glGetShaderInfoLog(shaderProgram, result, NULL, log.data());
                std::cerr << "Shader linking failed with error: " << log << '\n';
                return std::nullopt;
            }
            
            return shaderProgram;
        }
    private:
        std::filesystem::path &vert_path;
        std::optional<std::filesystem::path> tesselation_path;
        std::optional<std::filesystem::path> transform_path;
        std::filesystem::path &frag_path;
        std::optional<GLuint> generic_compile(std::filesystem::path &path) {
            std::ifstream filestream(path);
            if (filestream.fail()) {
                return std::nullopt;
            }
            std::string shader_code;
            filestream >> shader_code;
	        GLuint shader = glCreateShader(GL_VERTEX_SHADER);
            const GLchar *vertex_source = (const GLchar *)shader_code.c_str();
	        glShaderSource(shader, 1, &vertex_source, NULL);
	        glCompileShader(shader);
            GLint result = 0;
            glGetShaderiv(shader,  GL_COMPILE_STATUS, &result);
            // compilation failed
            if (!result) {
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &result);
                std::string log(result, ' ');
                glGetShaderInfoLog(shader, result, NULL, log.data());
                std::cerr << "Shader compilation failed with error: " << log << '\n';
                std::cerr << "Filepath for the shader that failed to compile: " << path << '\n';
                return std::nullopt;
            }
            return shader;
        }
};
