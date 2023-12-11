cmake_minimum_required(VERSION 3.26)
project(TrieProject)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(TrieProject
        main.cpp
        trie.cpp
        trie.h
        cmake-build-debug/words.txt)
