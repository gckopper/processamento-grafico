#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <string> 
#include <vaoBuilder.h>
#include <shader.h>
#include <vertShader.h>
#include <fragShader.h>

#include <iostream>

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

    std::cout << VERT_SOURCE << "\n\n";
    std::cout << FRAG_SOURCE << "\n\n";
    Shader shader(VERT_SOURCE, FRAG_SOURCE);
    std::optional<GLuint> shaderId = shader.compile();
    if (!shaderId.has_value()) {
        std::cout << "Shader compilation failed\n";
        return -1;
    }
    VAOBuilder vao_builder(shaderId.value());
    std::vector<GLfloat> vertex = {0.0, 0.6, -0.59, -0.49, 0.6, -0.3};
    std::vector<GLfloat> colors = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
    vao_builder.addData<GLfloat>("position", vertex);
    vao_builder.addData<GLfloat>("color", colors);
    GLuint vao = vao_builder.build();

	glUseProgram(shaderId.value());

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
