cmake_minimum_required(VERSION 4.1)
# set(CMAKE_CXX_COMPILER /usr/bin/g++-15)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)  
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

# Extrai versao do clang para caminho correto do llvm modules json
execute_process(
    COMMAND ${CMAKE_CXX_COMPILER} --version
    OUTPUT_VARIABLE _clang_version_output
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
string(REGEX MATCH "clang version ([0-9]+\\.[0-9]+)" _clang_version_match ${_clang_version_output})
set(_full_version ${CMAKE_MATCH_1})
string(REGEX REPLACE "\\..*" "" _major_version ${_full_version})
message(STATUS "Versão MAJOR Clang: ${_major_version}")
# CLANG BUG: https://github.com/llvm/llvm-project/issues/172497
set(CMAKE_CXX_STDLIB_MODULES_JSON "/usr/lib/llvm-${_major_version}/lib/libc++.modules.json" CACHE FILEPATH "JSON módulos do libc++ (Clang VERSAO ${_major_version})")


# https://github.com/Kitware/CMake/blob/master/Help/dev/experimental.rst
set (CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444") # 4.1
# set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "451f2fe2-a8a2-47c3-bc32-94786d8fc91b") # 4.3
set (CMAKE_CXX_MODULE_STD 1)
project(demo-project LANGUAGES CXX VERSION 0.0.1)
set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(lista01 INTERFACE)
target_include_directories(lista01 INTERFACE include/)

add_library(lista_modulo)
target_sources(lista_modulo  PUBLIC  FILE_SET CXX_MODULES FILES   src/lista_modulo.cppm)

#
Include(FetchContent)
FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git GIT_TAG 12.1.0)
FetchContent_MakeAvailable(fmt)
#
target_link_libraries(lista01 INTERFACE fmt)
add_executable(aplicacao src/main.cpp)
target_link_libraries(aplicacao PRIVATE lista01 fmt lista_modulo)
