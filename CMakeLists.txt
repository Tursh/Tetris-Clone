cmake_minimum_required(VERSION 3.14)

add_subdirectory(CrossGameEngine)

include_directories(CrossGameEngine/include)

project(Tetris)

set(CMAKE_CXX_STANDARD 17)

#Set preprossessor definitions
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -DNDEBUG")

include_directories(include)

#Set the output directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(Tetris src/main.cpp src/States/PlayingState.cpp include/States/PlayingState.h src/Grid/Grid.cpp include/Grid/Grid.h src/Grid/GridShader.cpp include/Grid/GridShader.h)

target_link_libraries(Tetris glfw GL freetype tinyxml2 GLEW)

target_link_libraries(Tetris CrossGameEngine)

add_custom_command(TARGET Tetris PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:Tetris>/res)