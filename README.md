# Processamento gráfico

Este repositório contém os trabalhos desenvolvidos durante e para a Atividade
Acadêmica (AA) de Processamento Gráfico (PG). Ele utiliza da ferramenta cmake
para compilar os códigos e testes.

## Compilando exercícios

<details><summary>Setup com o Mingw64 e ou Msys2</summary>
Para compilar os projetos em um ambiente Mingw64 ou Msys2 recomenda-se o uso do
pacote `mingw-w64-ucrt-x86_64-cmake` e de um compilador de C e C++ compativel com
o ambiente ucrt. Com as ferramentas em mãos, o processo é identico a compilação em
sistemas GNU/Linux.
</details>

Primeiramente clone este repositório:

```
git clone https://github.com/gckopper/processamento-grafico
```

Entre no diretorio do exercício desejado, por exemplo, `aula-01` usando o comando `cd`:

```
cd aula-01
```

Inicialize o cmake utilizando o comando abaixo junto de flags opcionais:

<details><summary>Compilar testes (opcional)</summary>
Ignore o comando abaixo e use:
```
cmake -S . -B build -DPACKAGE_TESTS=ON
```
</details>

```
cmake -S . -B build
```

Feito isso, basta compilar o projeto utilizando o comando:

```
cmake --build build
```

A primeira compilação é um pouco mais demorada, pois compilamos a GLFW na hora.
Esta compilação ocorre apenas uma vez sendo reutilizada em builds subsequentes
do mesmo projeto. A compilação da GLFW permite que o mesmo projeto seja
utilizado para múltiplos sistemas operacionais e arquiteturas sem que seja
necessário redistribuir binários para todos os possíveis alvos.

Os binários estarão na pasta `build/src/` em todos os alvos menos no Windows
usando o MSVC para a `aula-01` e `lista1`. Neste caso elas estarão em
`build/src/Debug/`.

Da `lista2` em diante, os binários ficam em `build/apps/<número do exercício>` ou
`build/apps/Debug/<número do exercício>` usando o MSVC.
