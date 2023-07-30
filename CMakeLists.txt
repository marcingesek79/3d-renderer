cmake_minimum_required(VERSION 3.8)
project("3d-rendering" LANGUAGES CXX)

find_package(Boost REQUIRED)
find_package(SFML COMPONENTS system window graphics REQUIRED)

add_executable(3d-rendering "main.cpp")
target_link_libraries(3d-rendering PRIVATE Boost::boost)
target_link_libraries(3d-rendering PRIVATE sfml-system sfml-window sfml-graphics)