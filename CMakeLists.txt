cmake_minimum_required( VERSION 3.0 )

project( RaspiRemoteCam )


# flags

# include files
include_directories( ./include ./src ./libs/pigpio/include ./libs/SG90/include ./libs/FaceTrackingCamera/include )
add_subdirectory( ./libs/SG90 )
add_subdirectory( ./libs/FaceTrackingCamera )
# target
add_executable( TheProgram ./src/core/RaspiRemoteCam.cpp )


#libs

target_link_libraries( TheProgram SG90 )
target_link_libraries( TheProgram FaceTrackingCamera )
add_library(pigpio SHARED IMPORTED)
set_property(TARGET pigpio PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/pigpio/libpigpio.so)
target_link_libraries( TheProgram pigpio )
