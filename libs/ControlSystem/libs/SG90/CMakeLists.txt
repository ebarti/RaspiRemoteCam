cmake_minimum_required( VERSION 3.0 )

project( lib_SG90 )

# flags

# include files
include_directories( ./include ./src )

# target

add_library(SG90 SHARED ./src/SG90.cpp)

# install(TARGETS SG90 DESTINATION ${CMAKE_SOURCE_DIR})
# install(TARGETS SG90.h DESTINATION lib)