cmake_minimum_required(VERSION 3.14)

set(BUILD_SHARED_LIBS ON)

#Set the output directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(CrossGameEngine)

include_directories(CrossGameEngine/include)


project(Tetris)



set(CMAKE_CXX_STANDARD 17)

#Set preprossessor definitions
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -DNDEBUG")

include_directories(include)

link_libraries(CrossGameEngine)

if (NOT WIN32)
    link_libraries(GL harfbuzz)
else ()
    link_libraries(opengl32)
endif ()

if (NOT BUILD_SHARED_LIBS)
    if (NOT WIN32)
        link_libraries(freetype GLEW glfw tinyxml2)
    else ()
        link_libraries(freetype glew32 glfw3 tinyxml2)
    endif ()
endif ()

add_executable(Tetris
        src/main.cpp
        src/States/PlayingState.cpp
        src/Grid/Grid.cpp
        src/Grid/GridShader.cpp
        src/States/LosingState.cpp
        )

add_custom_command(TARGET Tetris PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:Tetris>/res)