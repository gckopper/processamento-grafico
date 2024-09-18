#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <vaoBuilder.h>
#include <twod.h>
#include <shader.h>
#include <vertShader.h>
#include <fragShader.h>

#include <string> 
#include <iostream>

const GLuint WIDTH = 800;
const GLuint HEIGHT = 800;

int main() {
    glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Criação da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Gabriel Kopper - Exercicio nove - Cat", nullptr, nullptr);
	glfwMakeContextCurrent(window);
    if (gladLoadGL(glfwGetProcAddress) == 0) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

    Shader shader(VERT_SOURCE, FRAG_SOURCE);
    std::optional<GLuint> shaderId = shader.compile();
    if (!shaderId.has_value()) {
        std::cout << "Shader compilation failed\n";
        return -1;
    }
    VAOBuilder vao_builder(shaderId.value());
    std::vector<GLint> starts;
    std::vector<GLsizei> counts;

    std::vector<twod::Vertex> vertex = twod::make_convex_regular_polygon(90, 0.5, {0.0f, 0.0f});
    std::vector<float> color_face(vertex.size()*3, 0.4);
    vao_builder.addData<twod::Vertex>("position", vertex);
    vao_builder.addData<GLfloat>("color", color_face);
    starts.push_back(0);
    counts.push_back(vertex.size());
    // arr size
    uint64_t total_size = 0;
    // adiciona os olhos
    vertex.clear();
    vertex = twod::make_elipse(90, 0.1, 1, 2, {-0.2, 0.075});
    total_size += vertex.size();
    vao_builder.addData<twod::Vertex>("position", vertex);
    starts.push_back(starts.back()+counts.back());
    counts.push_back(vertex.size());
    // adiciona os olhos
    vertex.clear();
    vertex = twod::make_elipse(90, 0.1, 1, 2, {0.2, 0.075});
    total_size += vertex.size();
    vao_builder.addData<twod::Vertex>("position", vertex);
    starts.push_back(starts.back()+counts.back());
    counts.push_back(vertex.size());
    // adiciona as boca
    vertex.clear();
    vertex = twod::make_convex_regular_polygon(90, 0.1, {0.0f, -0.2f});
    total_size += vertex.size();
    vao_builder.addData<twod::Vertex>("position", vertex);
    starts.push_back(starts.back()+counts.back());
    counts.push_back(vertex.size());
    // adiciona as orelhas
    vertex.clear();
    vertex.push_back({-0.1, 0.49});
    vertex.push_back({-0.4, 0.3});
    vertex.push_back({-0.4, 0.9});
    starts.push_back(starts.back()+counts.back());
    counts.push_back(3);
    vertex.push_back({0.1, 0.49});
    vertex.push_back({0.4, 0.3});
    vertex.push_back({0.4, 0.9});
    starts.push_back(starts.back()+counts.back());
    counts.push_back(3);
    // adiciona o treco
    vertex.push_back({-0.21, -0.11});
    vertex.push_back({-0.20, -0.10});
    vertex.push_back({-0.6, 0.0});
    vertex.push_back({-0.6, 0.0});
    vertex.push_back({-0.61, -0.01});
    starts.push_back(starts.back()+counts.back());
    counts.push_back(5);
    vertex.push_back({0.21, -0.11});
    vertex.push_back({0.20, -0.10});
    vertex.push_back({0.6, 0.0});
    vertex.push_back({0.6, 0.0});
    vertex.push_back({0.61, -0.01});
    starts.push_back(starts.back()+counts.back());
    counts.push_back(5);
    vertex.push_back({-0.21, -0.31});
    vertex.push_back({-0.20, -0.30});
    vertex.push_back({-0.60, -0.40});
    vertex.push_back({-0.60, -0.40});
    vertex.push_back({-0.61, -0.41});
    starts.push_back(starts.back()+counts.back());
    counts.push_back(5);
    vertex.push_back({0.21, -0.31});
    vertex.push_back({0.20, -0.30});
    vertex.push_back({0.60, -0.40});
    vertex.push_back({0.60, -0.40});
    vertex.push_back({0.61, -0.41});
    starts.push_back(starts.back()+counts.back());
    counts.push_back(5);
    vertex.push_back({-0.20, -0.21});
    vertex.push_back({-0.20, -0.20});
    vertex.push_back({-0.60, -0.20});
    vertex.push_back({-0.60, -0.20});
    vertex.push_back({-0.60, -0.21});
    starts.push_back(starts.back()+counts.back());
    counts.push_back(5);
    vertex.push_back({0.20, -0.21});
    vertex.push_back({0.20, -0.20});
    vertex.push_back({0.60, -0.20});
    vertex.push_back({0.60, -0.20});
    vertex.push_back({0.60, -0.21});
    starts.push_back(starts.back()+counts.back());
    counts.push_back(5);

    total_size += vertex.size();
    vao_builder.addData<twod::Vertex>("position", vertex);

    std::vector<float> colors(total_size*3, 0.8);
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
        glMultiDrawArrays(GL_TRIANGLE_FAN, starts.data(), counts.data(), starts.size());
		glBindVertexArray(0); //Desconectando o buffer de geometria

		// Troca os buffers da tela
		glfwSwapBuffers(window);
    }
	glDeleteVertexArrays(1, &vao);

	glfwTerminate();
	return 0;
}
