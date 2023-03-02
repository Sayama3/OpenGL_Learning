cmake_minimum_required(VERSION 3.24)
project(OpenGL_Learning)

add_subdirectory(glfw)

target_link_libraries(OpenGL PUBLIC glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(OpenGL PUBLIC OpenGL::GL)


set(glew-cmake_BUILD_SHARED FALSE)
set(glew-ONLY_LIBS ON)
add_subdirectory(glew)
target_link_libraries(OpenGL PUBLIC libglew_static)

add_subdirectory(glm)
target_link_libraries(OpenGL PUBLIC glm)

