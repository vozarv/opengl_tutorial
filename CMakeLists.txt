cmake_minimum_required(VERSION 3.9.0)

project(OpenGL_tutorial VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(OpenGL_tutorial 
    src/main.cpp
    src/display.cpp
    #src/shader.cpp
    #src/mesh.cpp
    src/stb_image.c
    #src/texture.cpp
    src/obj_loader.cpp
    src/control.cpp
    src/camera.cpp
    src/player.cpp
    src/background.cpp
    )


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(glm REQUIRED) 
find_package(glfw3 3.3 REQUIRED)
find_package(assimp REQUIRED)

if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} OpenGL)
endif()

target_link_libraries(
    ${PROJECT_NAME} 
            GLEW::GLEW 
            SDL2::SDL2 
            glm::glm 
            glfw 
            SDL2::SDL2main 
            assimp::assimp) 

add_custom_command(
  TARGET OpenGL_tutorial
  PRE_BUILD
  COMMAND ${CMAKE_COMMAND}
  ARGS -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
  )

