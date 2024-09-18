# Lista de exercícios 1

## 1. O que é a GLSL? Quais os dois tipos de shaders são obrigatórios no pipeline programável da versão atual que trabalhamos em aula e o que eles processam?

GLSL é a linguagem de programação de shaders criada pelo Khronos Group para uso
no OpenGL. Os shaders obrigatórios são o vertex shader e o fragment shader.
O vertex shader processar os vértices das formas geométricas que vamos desenhar,
a forma específica é especificada pela primitiva usada. O shader de fragmento 
define a cor de cada um dos fragmentos.

## 2. O que são primitivas gráficas? Como fazemos o armazenamento dos vértices na OpenGL?

As primitivas gráficas indicam para o OpenGL como desenhar nossos vértices.

Os vértices são, inicialmente, armazenados em buffers chamados *Vertex Buffer
Objects* e depois eles vão para a GPU.

## 3. Explicando VBOs, VAOs e EBOs

- VBO (Vertex Buffer Object):

Vertex Buffer Objects guardam os dados que usamos para desenhar os vértices.
Nos exercícios, usamos VBOs para guardar as coordenadas dos vértices e suas
cores. Esses buffers vivem na memória da GPU para serem acessados durante
o processamento dos shaders.

- VAO (Vertex Array Object):

Usamos o VAOs para indicar como os dados do VBO se relacionam com os atributos
de um shader. O VAO também guarda a informação de qual o EBO que está em uso.

- EBO (Element Buffer Object):

O EBO é usado para guardar os índices do VBO que serão usados por cada vértice.

## 4. sem entrega

## 5. Desenhando triângulos

[Fonte](src/cinco.cpp)

![](images/cinco.png)

## 6. Círculos, estrelas e pizza

[Fonte](src/seis.cpp)

![](images/seis.png)

## 7. Espiral

[Fonte](src/sete.cpp)

![](images/sete.png)

## 8. Triangulo tri

[Fonte](src/oito.cpp)
![](images/oito.png)

## 9. Papel

[Fonte](src/nove.cpp)
[Projeto do Excalidraw](images/nove.excalidraw)

### Ideia

![](images/nove-draw.png)

### Resultado

![](images/nove.png)
