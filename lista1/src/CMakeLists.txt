add_executable(cinco cinco.cpp)
target_link_libraries(cinco PUBLIC glfw glad)

add_executable(seis seis.cpp)
target_link_libraries(seis PUBLIC glfw glad simpleTwodVaoBuilder twod)

add_executable(sete sete.cpp)
target_link_libraries(sete PUBLIC glfw glad simpleTwodVaoBuilder twod)

add_executable(oito oito.cpp)
target_link_libraries(oito PUBLIC glfw glad vaoBuilder)

file(READ ../shaders/nove.vert FILE_CONTENT)
set(SHADER_NAME "VERT_SOURCE")
configure_file(../templates/shaderSource.h.in "${CMAKE_BINARY_DIR}/generated_headers/vertShader.h" @ONLY)
file(READ ../shaders/nove.frag FILE_CONTENT)
set(SHADER_NAME "FRAG_SOURCE")
configure_file(../templates/shaderSource.h.in "${CMAKE_BINARY_DIR}/generated_headers/fragShader.h" @ONLY)
add_executable(nove nove.cpp)
target_link_libraries(nove PUBLIC glfw glad vaoBuilder shader twod)
