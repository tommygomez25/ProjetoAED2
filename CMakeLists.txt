cmake_minimum_required(VERSION 3.21)
project(ProjetoAED2)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/dataset")

add_executable(ProjetoAED2 main.cpp Graph.cpp Graph.h)

