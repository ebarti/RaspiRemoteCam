cmake_minimum_required( VERSION 3.0 )

project( RaspiRemoteCam )

# flags

# include files
include_directories( ./include ./src ./libs/pigpio/include )

# target
add_executable( TheProgram ./src/RaspiRemoteCam.cpp )


#libs

# add_subdirectory( ./libs/pigpio )
# target_link_libraries( TheProgram pigpio )

add_library(pigpio SHARED IMPORTED)
set_property(TARGET pigpio PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/pigpio/libpigpio.so)
target_link_libraries( TheProgram pigpio )