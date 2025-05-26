cmake_minimum_required(VERSION 3.10)

project(MyProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable and all cpp files
add_executable(MyProject
        dspotify25b1.cpp
        main25b1.cpp
        dspotify25b1.h
        wet1util.h
        song.h
        song.cpp
        node.h
        playlist.h
        playlist.cpp
        RealValueFunctions.cpp
        song.h
        AVL_trees.h
)