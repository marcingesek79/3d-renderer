﻿cmake_minimum_required(VERSION 3.8)
project("3d-renderer" LANGUAGES CXX)

find_package(SFML COMPONENTS system window graphics REQUIRED)

add_executable(3d-renderer "src/main.cpp" "src/renderer.cpp")

target_compile_features(3d-renderer PUBLIC cxx_std_17)

target_include_directories(3d-renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(3d-renderer PRIVATE sfml-system sfml-window sfml-graphics)
