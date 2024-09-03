# Lista de exercícios 1

## 1. O que é a GLSL? Quais os dois tipos de shaders são obrigatórios no pipeline programável da versão atual que trabalhamos em aula e o que eles processam?

GLSL é a linguagem de programação de shaders criada pelo Khronos Group para uso
no OpenGL. Os shaders obrigatórios são o vertex shader e o fragment shader.
O vertex shader processar os vértices das formas geométricas que vamos desenhar,
a forma específica é especificada pela primitiva usada. O shader de fragmento 
define a cor de cada um dos fragmentos.

## 2. O que são primitivas gráficas? Como fazemos o armazenamento dos vértices na OpenGL?

As primitivas gráficas indicam para o OpenGL como desenhar nossos vértices.

Os vértices são armazenados, inicialmente, em buffers chamados Vertex Buffer
Objects e depois passados para um Vertex Array Object (VAO).
