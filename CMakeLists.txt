cmake_minimum_required(VERSION 3.9.0)
project(OpenGL_tutorial VERSION 0.1.0 LANGUAGES CXX)

include(CTest)
enable_testing()

add_executable(OpenGL_tutorial 
    src/main.cpp
    src/display.cpp
    src/shader.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(glm REQUIRED) 

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res
DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


target_link_libraries(${PROJECT_NAME} GLEW::GLEW SDL2 glm::glm OpenGL) 