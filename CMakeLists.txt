cmake_minimum_required(VERSION 3.25.1)

project(nbody)

set(PROJECT_SOURCES
    main.c
    src/nbody.c
    src/body.c
)

add_subdirectory(deps/List)
add_subdirectory(deps/Vec)
add_subdirectory(deps/SDL3)
add_subdirectory(deps/SDL3_TTF)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/deps/List)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/deps/Vec)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/deps/SDL3_TTF)

target_link_libraries(${PROJECT_NAME} PRIVATE pthread)

target_link_libraries(nbody PUBLIC list)
target_link_libraries(nbody PUBLIC vec2)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_ttf-shared)