# Author: Jeroen de Haas <jah.dehaas@avans.nl>
cmake_minimum_required(VERSION 3.1.3)
project(kmintapp)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (MSVC)
    add_compile_options(/W3)
else ()
    add_compile_options(-Wall -Wpedantic)
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif ()


add_executable(kmintapp
        src/main.cpp
        src/actors/cow.cpp
        src/actors/cow.h
        src/actors/hare.cpp
        src/actors/hare.h
        src/actors/tester.h
        src/drawables/rectangle.h
        src/pathfinding/dijkstra.cpp
        src/pathfinding/dijkstra.h
        src/pathfinding/pathfinder.h
        src/pathfinding/path.h src/pathfinding/astar.cpp src/pathfinding/astar.h)

target_compile_features(kmintapp PUBLIC cxx_std_17)
target_link_libraries(kmintapp PRIVATE kmint)
target_include_directories(kmintapp PRIVATE
        src)

add_custom_target(resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/resources" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources")
