cmake_minimum_required(VERSION 3.21)
project(wet1)

set(CMAKE_CXX_STANDARD 14)

add_executable(wet1 main.cpp cmake-build-debug/AVL_Tree.cpp cmake-build-debug/AVL_Tree.h cmake-build-debug/BST.cpp cmake-build-debug/BST.h cmake-build-debug/Node.cpp cmake-build-debug/Node.h cmake-build-debug/A_Node.cpp cmake-build-debug/A_Node.h)
