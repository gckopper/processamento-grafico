add_shader("VERT_SHADER" "shaderSource.h.in" "um.vert" "umVertShader.h")
add_shader("FRAG_SHADER" "shaderSource.h.in" "um.frag" "umFragShader.h")
add_executable(um um.cpp)
target_link_libraries(um PUBLIC glfw glad vaoBuilder shader glm)

add_executable(dois dois.cpp)
target_link_libraries(dois PUBLIC glfw glad vaoBuilder shader glm)
