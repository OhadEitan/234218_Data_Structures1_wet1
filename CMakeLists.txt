cmake_minimum_required(VERSION 3.21)
project(wet1_new)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        wet1_new
        main.cpp
        wet1util.h
        Player.cpp
        Player.h
        AVLTree.h
        Team.cpp
        Team.h
        worldcup23a1.h
        worldcup23a1.cpp
        merge.h
        LinkedList.h)
