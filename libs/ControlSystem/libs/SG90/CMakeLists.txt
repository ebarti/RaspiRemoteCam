cmake_minimum_required( VERSION 3.15 )
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project( lib_SG90 )

add_library(lib_SG90 SHARED src/SG90.cpp)

add_library(SG90::library ALIAS lib_SG90)

target_include_directories(lib_SG90 #include <SG90.h>
	PUBLIC 
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${CMAKE_CURRENT_SOURCE_DIR}/libs/pigpio/include 
)

add_library(pigpio SHARED IMPORTED)
set_property(TARGET pigpio PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/pigpio/libpigpio.so)

target_link_libraries( lib_SG90 pigpio )
