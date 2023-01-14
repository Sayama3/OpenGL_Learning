cmake_minimum_required(VERSION 3.24)

add_library(GLEW bin/Release/x64/glew32.dll)
set_target_properties(GLEW PROPERTIES LINKER_LANGUAGE C)
include_directories(include)