cmake_minimum_required(VERSION 3.25.1)

project(nbody)

set(PROJECT_SOURCES 
    nbody.c
    src/body.c
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE pthread)

add_subdirectory(deps/List)
target_link_libraries(nbody PUBLIC list)

add_subdirectory(deps/SDL3)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)