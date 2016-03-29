cmake_minimum_required(VERSION 3.4)

project(EP1 C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES src/simulador.c src/simulador.h src/entrada/entrada.c src/entrada/entrada.h src/messages/messages.c src/messages/messages.h src/memory/central_memory.c src/events/EV1-NewJobs.c src/events/EV2-MemoryAloc.c src/events/EV3-CPUExec.c src/events/EV4-ReleaseCPU.c src/events/EV5-IOExecution.c src/events/EV6-ReleaseIO.c src/events/EV7-ReleaseALL.c src/events/EV1-NewJobs.h src/events/EV2-MemoryAloc.h src/events/EV3-CPUExec.h src/events/EV4-ReleaseCPU.h src/events/EV5-IOExecution.h src/events/EV6-ReleaseIO.h src/events/EV7-ReleaseAll.h src/utils/utils.c src/utils/utils.h)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(EP1 ${SOURCE_FILES})