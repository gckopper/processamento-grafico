#include <array>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <vaoBuilder.h>
#include <twod.h>

#include <iostream>

const GLchar* vertexShaderSource = R"v(
#version 330 core
layout (location = 0) in vec2 position;
void main() {
    // 2D only
    gl_Position = vec4(position.xy, 1.0, 1.0);
};
)v";

const GLchar* fragmentShaderSource = R"f(
#version 330 core
out vec4 color;
void main() {
    color = vec4(0.8, 0.0, 0.3, 1.0);
};
)f";
GLuint setupShader()
{
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// Checando erros de compilação (exibição via log no terminal)
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Checando erros de compilação (exibição via log no terminal)
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Linkando os shaders e criando o identificador do programa de shader
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Checando por erros de linkagem
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

const GLuint WIDTH = 800;
const GLuint HEIGHT = 800;


int main() {
    glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Criação da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Gabriel Kopper - Triangulos", nullptr, nullptr);
	glfwMakeContextCurrent(window);
    if (gladLoadGL(glfwGetProcAddress) == 0) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

    GLuint shader = setupShader();
    VAOBuilder vao_builder;
    twod::Vertex middle(0.0f, 0.0f);
    uint32_t num_vert;
    {
        std::vector<twod::Vertex> spiral= twod::make_spiral(0.8f, 0.2, middle);
        num_vert = spiral.size();
        vao_builder.addVertexArray(spiral);
    }
    GLuint vao = vao_builder.build();

	glUseProgram(shader);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.f, 0.f, 0.f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        glLineWidth(8);
        glPointSize(24);

		glBindVertexArray(vao); //Conectando ao buffer de geometria
		glDrawArrays(GL_LINE_STRIP, 0, num_vert);
		glBindVertexArray(0); //Desconectando o buffer de geometria

		// Troca os buffers da tela
		glfwSwapBuffers(window);
    }
	glDeleteVertexArrays(1, &vao);

	glfwTerminate();
	return 0;
}

