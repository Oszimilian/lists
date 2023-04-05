cmake_minimum_required(VERSION 3.12)

project(ring)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(${PROJECT_NAME} main.cpp ring.h crossi_ring_buf.h newring.h list_mtx.h)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)