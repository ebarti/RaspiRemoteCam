cmake_minimum_required( VERSION 3.15 )
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project( lib_SG90 )

set(pigpio_ROOT_DIR "/home/pi/pigpio/*")

find_package(pigpio REQUIRED)

message("Includes pigpio" ${pigpio_INCLUDE_DIRS})
message("Lib pigpio" ${pigpio_LIBS})

add_library(lib_SG90 SHARED ${CMAKE_CURRENT_SOURCE_DIR}/include/SG90.h ${CMAKE_CURRENT_SOURCE_DIR}/src/SG90.cpp)

add_library(SG90::library ALIAS lib_SG90)

target_include_directories(lib_SG90 #include <SG90.h>
	PUBLIC 
		${pigpio_INCLUDE_DIRS}
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${CMAKE_CURRENT_SOURCE_DIR}/src
)


target_link_libraries( lib_SG90 pigpio )
