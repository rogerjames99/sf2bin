cmake_minimum_required(VERSION 3.0.0)
project(sf2bin VERSION 0.1.0 LANGUAGES C CXX)

add_executable(sf2bin main.cpp)

target_include_directories(sf2bin PUBLIC "${CMAKE_SOURCE_DIR}/cereal/include")
