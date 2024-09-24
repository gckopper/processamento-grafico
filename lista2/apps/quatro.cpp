#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vaoBuilder.h>
#include <shader.h>
#include <umVertShader.h>
#include <umFragShader.h>

#include <iostream>

const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;

int main() {
    glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Criação da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Gabriel Kopper - Exercicio quatro - Lista 2", nullptr, nullptr);
	glfwMakeContextCurrent(window);
    if (gladLoadGL(glfwGetProcAddress) == 0) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
	glViewport(width/2, height/2, width/2, height/2);

    Shader shader(VERT_SHADER, FRAG_SHADER);
    std::optional<GLuint> shaderId = shader.compile();
    if (!shaderId.has_value()) {
        std::cout << "Shader compilation failed\n";
        return -1;
    }
    VAOBuilder vao_builder(shaderId.value());
    std::vector<float> vertexes = {-0.5, -0.5, 0.5, -0.5, 0.0, 0.5};
    vao_builder.addData<float>("position", vertexes);
    GLuint vao = vao_builder.build();

    glm::mat4 projection = glm::ortho(-1.0f,1.0f,-1.0f,1.0f,-1.0f,1.0f);

	glUseProgram(shaderId.value());

    glUniformMatrix4fv(glGetUniformLocation(shaderId.value(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao); //Conectando ao buffer de geometria
        glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0); //Desconectando o buffer de geometria

		// Troca os buffers da tela
		glfwSwapBuffers(window);
    }
	glDeleteVertexArrays(1, &vao);

	glfwTerminate();
	return 0;
}
