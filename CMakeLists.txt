cmake_minimum_required(VERSION 3.25.1)

project(nbody)

add_executable(${PROJECT_NAME} nbody.c)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)

add_subdirectory(deps/SDL3)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)