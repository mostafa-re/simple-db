cmake_minimum_required(VERSION 3.10)

project(sdb VERSION 1.73)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED true)

set(SOURCE src/main.c src/custom_io_module.c src/table_module.c src/table_manager_module.c)
set(COMPILE_FLAGS "-Wall -Wextra -g") # for dedugging :D

include_directories(include)
set(CMAKE_C_FLAGS ${COMPILE_FLAGS})
add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} m)