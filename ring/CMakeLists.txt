cmake_minimum_required(VERSION 3.12)

project(ring)

add_executable(${PROJECT_NAME} main.cpp ring.h crossi_ring_buf.h)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)