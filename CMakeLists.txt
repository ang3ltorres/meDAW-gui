cmake_minimum_required(VERSION 3.28)
project(medaw VERSION 0.0.1 LANGUAGES CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Source files
file(GLOB_RECURSE SOURCES_SGLF CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/medawgui/src/*.cpp)

# Define the library
add_library(medawgui ${SOURCES_SGLF})

# Include directories
target_include_directories(medawgui PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/medawgui/include
	${CMAKE_CURRENT_SOURCE_DIR}/build/dep/include
)

# Precompiled headers
target_precompile_headers(medawgui PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/medawgui/include/pch.hpp
)

# Compilation options
target_compile_options(medawgui PRIVATE -Wall -Wextra -Wpedantic -fmax-errors=1)

# Link dependencies
target_link_directories(medawgui PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/build/dep/bin
)

target_link_libraries(medawgui PUBLIC
	glfw
	GLEW
	freetype
	png
	plutosvg
	plutovg
	GL
)

# Test Executable
file(GLOB_RECURSE SOURCES_TEST CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test/src/*.cpp)
add_executable(test ${SOURCES_TEST})
target_include_directories(test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/test/include" "${CMAKE_CURRENT_SOURCE_DIR}/include)
target_precompile_headers(test REUSE_FROM medawgui)
target_compile_options(test PRIVATE -Wall -Wextra -Wpedantic -fmax-errors=1)
target_link_libraries(test PRIVATE medawgui)
