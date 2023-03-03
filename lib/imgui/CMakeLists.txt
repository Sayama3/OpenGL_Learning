cmake_minimum_required(VERSION 3.24)

project(imgui VERSION 1.89.4 DESCRIPTION "The library Dear ImGUI by Omar Cornut in from the docking branch.")

include(GNUInstallDirs)

add_library(imgui
        src/imgui.cpp
        src/imgui_demo.cpp
        src/imgui_draw.cpp
        src/imgui_impl_glfw.cpp
        src/imgui_impl_opengl3.cpp
        src/imgui_tables.cpp
        src/imgui_widgets.cpp
        )


set_target_properties(imgui PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(imgui PROPERTIES SOVERSION 1)

target_include_directories(imgui PUBLIC include)

target_link_libraries(imgui glfw OpenGL::GL libglew_static)

#install(TARGETS imgui
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
#
#configure_file(imgui.pc.in imgui.pc @ONLY)
#
#install(FILES ${CMAKE_BINARY_DIR}/imgui.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
