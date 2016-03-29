cmake_minimum_required(VERSION 3.4)

project(EP1 C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES src/simulador.c src/simulador.h src/entrada/entrada.c src/entrada/entrada.h src/messages/messages.c src/messages/messages.h src/memory/central_memory.c)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(EP1 ${SOURCE_FILES})