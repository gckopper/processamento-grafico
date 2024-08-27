#include <cmath>
#include <glad/gl.h>

#include <GLFW/glfw3.h>
#include <iostream>
#include <array>
#include <vector>

typedef std::array<float, 3> vec3;
typedef std::array<std::pair<float, float>, 3> triangle;

// Esta função está bastante harcoded - objetivo é criar os buffers que armazenam a 
// geometria de um triângulo
// Apenas atributo coordenada nos vértices
// 1 VBO com as coordenadas, VAO com apenas 1 ponteiro para atributo
// A função retorna o identificador do VAO
GLuint setupTriangleGeometry(triangle tri, std::vector<float> rot)
{

    std::vector<GLfloat> vertices(9*rot.size());

    for (int i = 0; i < rot.size(); ++i) {
        const float co = std::cos(rot[i]);
        const float si = std::sin(rot[i]);
        for (int j = 0; j < 3; ++j) {
            vertices[i*9+j*3]   = tri[j].first*co - tri[j].second*si;
            vertices[i*9+j*3+1] = tri[j].second*co + tri[j].first*si;
            vertices[i*9+j*3+2] = 1.0f;
        }
    }

	GLuint VBO, VAO;
	//Geração do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conexão (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	//Geração do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se está normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0); 

	return VAO;
}

const GLchar* vertexShaderSource = R"v(
#version 330 core
layout (location = 0) in vec3 position;
void main() {
    // 2D only
    gl_Position = vec4(position.xyz, 1.0);
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
    const triangle tri = {std::pair<float, float>{0.f, 1.0f},{std::sqrt(0.12f), 0.6f},{-std::sqrt(0.12f), 0.6f}};
    GLuint vao = setupTriangleGeometry(tri, {0.0f, M_PIf, (1.f/3.f)*M_PIf, (4.f/3.f)*M_PIf, (2.f/3.f)*M_PIf, (5.f/3.f)*M_PIf});

    std::vector<int> polygon_modes = {GL_FILL, GL_LINE, GL_POINT};

	glUseProgram(shader);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.f, 0.f, 0.f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        glLineWidth(8);
        glPointSize(24);

		glBindVertexArray(vao); //Conectando ao buffer de geometria
        for (unsigned int i = 0; i < polygon_modes.size(); ++i) {

            glPolygonMode(GL_FRONT_AND_BACK, polygon_modes[i]);

		    glDrawArrays(GL_TRIANGLES, i*6, 6);

        }
		glBindVertexArray(0); //Desconectando o buffer de geometria

		// Troca os buffers da tela
		glfwSwapBuffers(window);
    }
	glDeleteVertexArrays(1, &vao);

	glfwTerminate();
	return 0;
}

