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

#=======================================================
add_executable(HelloTransformations
    source/transformations/transformations.cpp
    source/glad.c
    source/stb_image.cpp
    )
target_link_libraries(HelloTransformations
    ${PROJECT_SOURCE_DIR}/libs/lib-mingw-w64/libglfw3.a
    )

#=======================================================
add_executable(HelloTransformations2
    source/transformations/transformations2.cpp
    source/glad.c
    source/stb_image.cpp
    )
target_link_libraries(HelloTransformations2
    ${PROJECT_SOURCE_DIR}/libs/lib-mingw-w64/libglfw3.a
    )

#=======================================================
add_executable(HelloCoordinateSystems
    source/coordinate_systems/coordinate_systems.cpp
    source/glad.c
    source/stb_image.cpp
    )
target_link_libraries(HelloCoordinateSystems
    ${PROJECT_SOURCE_DIR}/libs/lib-mingw-w64/libglfw3.a
    )

#=======================================================
add_executable(HelloCoordinateSystemsDpeth
    source/coordinate_systems/coordinate_systems_depth.cpp
    source/glad.c
    source/stb_image.cpp
    )
target_link_libraries(HelloCoordinateSystemsDpeth
    ${PROJECT_SOURCE_DIR}/libs/lib-mingw-w64/libglfw3.a
    )

#=======================================================
add_executable(HelloCamerCircle
    source/camera_circle/camera_circle.cpp
    source/glad.c
    source/stb_image.cpp
    )
target_link_libraries(HelloCamerCircle
    ${PROJECT_SOURCE_DIR}/libs/lib-mingw-w64/libglfw3.a
    )