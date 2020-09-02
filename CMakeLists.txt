cmake_minimum_required(VERSION 3.17)
project(bgfx_test)

set(CMAKE_CXX_STANDARD 17)

include_directories("core")
file(GLOB_RECURSE SOURCES core/*.cpp)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

add_subdirectory(libs/bgfx)
target_link_libraries(${PROJECT_NAME} PRIVATE bgfx)

add_subdirectory(libs/AudioMoon)
target_link_libraries(${PROJECT_NAME} PRIVATE AudioMoon)
