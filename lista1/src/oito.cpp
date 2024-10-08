#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <string> 
#include <vaoBuilder.h>

#include <iostream>

const GLchar* vertexShaderSource = R"v(
#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
out vec3 vcolor;
void main() {
    // 2D only
    gl_Position = vec4(position.xy, 1.0, 1.0);
    vcolor = color;
};
)v";

const GLchar* fragmentShaderSource = R"f(
#version 330 core
in vec3 vcolor;
out vec4 color;
void main() {
    color = vec4(vcolor.xyz, 1.0);
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
    VAOBuilder vao_builder(shader);
    std::vector<GLfloat> vertex = {0.0, 0.6, -0.59, -0.49, 0.6, -0.3};
    std::vector<GLfloat> colors = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
    vao_builder.addData<GLfloat>("position", vertex);
    vao_builder.addData<GLfloat>("color", colors);
    GLuint vao = vao_builder.build();

	glUseProgram(shader);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.f, 0.f, 0.f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        glLineWidth(8);
        glPointSize(24);

		glBindVertexArray(vao); //Conectando ao buffer de geometria
		glDrawArrays(GL_POINTS, 0, 3);
		glBindVertexArray(0); //Desconectando o buffer de geometria

		// Troca os buffers da tela
		glfwSwapBuffers(window);
    }
	glDeleteVertexArrays(1, &vao);

	glfwTerminate();
	return 0;
}
