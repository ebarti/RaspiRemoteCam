cmake_minimum_required( VERSION 3.0 )

project( RaspiRemoteCam )

# flags

# include files
include_directories( ./include ./src/servoctl/LocalInterfaces ./libs/pigpio/include )

# target
add_executable( TheProgram ./src/core/RaspiRemoteCam.cpp ./src/servoctl/SG90.cpp)


#libs

# add_subdirectory( ./libs/pigpio )
# target_link_libraries( TheProgram pigpio )

add_library(pigpio SHARED IMPORTED)
set_property(TARGET pigpio PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/pigpio/libpigpio.so)
target_link_libraries( TheProgram pigpio )