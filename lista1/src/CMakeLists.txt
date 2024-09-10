add_executable(cinco cinco.cpp)
target_link_libraries(cinco PUBLIC glfw glad)

add_executable(seis seis.cpp)
target_link_libraries(seis PUBLIC glfw glad vaoBuilder twod)
