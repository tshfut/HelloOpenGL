cmake_minimum_required(VERSION 3.23)
project(HelloOpenGL)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS -static)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

#=======================================================
add_executable(HelloMain
    source/main.cpp
    source/glad.c
    )
target_link_libraries(HelloMain
    ${PROJECT_SOURCE_DIR}/libs/lib-mingw-w64/libglfw3.a
    )

#=======================================================
add_executable(HelloShaderHelper
    source/ShaderClass/HelloShaderHelper.cpp
    source/glad.c
    )
target_link_libraries(HelloShaderHelper
    ${PROJECT_SOURCE_DIR}/libs/lib-mingw-w64/libglfw3.a
    )

